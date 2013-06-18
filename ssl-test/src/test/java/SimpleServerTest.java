import com.sun.net.httpserver.*;
import org.junit.Test;

import javax.net.ssl.*;
import java.io.*;
import java.net.HttpURLConnection;
import java.net.InetSocketAddress;
import java.net.URL;
import java.security.*;
import java.security.cert.CertificateException;
import java.security.cert.X509Certificate;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/**
 *
 */
public class SimpleServerTest {

    static class MyHandler implements HttpHandler {
        public void handle(HttpExchange t) throws IOException {

                String response = "This is the response";
                t.sendResponseHeaders(200, response.length());
                OutputStream os = t.getResponseBody();
                os.write(response.getBytes());

        }
    }

    @Test
    public void testSimpleServer() throws IOException, InterruptedException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 5);
        server.createContext("/applications/myapp", new MyHandler());

        ExecutorService executor = Executors.newFixedThreadPool(5);
        server.setExecutor(executor); // creates a default executor
        server.start();
        executor.awaitTermination(Integer.MAX_VALUE, TimeUnit.DAYS);
    }

    @Test
    public void testHttpsServer()
        throws IOException, KeyManagementException, NoSuchAlgorithmException, CertificateException, KeyStoreException,
               UnrecoverableKeyException, InterruptedException {
        HttpsServer server = HttpsServer.create(new InetSocketAddress(8000), 5);
        server.createContext("/", new MyHandler());

        char[] storepass = "storepass".toCharArray();
        char[] keypass = "serverpass".toCharArray();

        KeyStore ks = KeyStore.getInstance("JKS");
        ks.load(SimpleServerTest.class.getResourceAsStream("server.jks"), storepass);

        KeyManagerFactory kmf = KeyManagerFactory.getInstance("SunX509");
        kmf.init(ks, keypass);

        SSLContext sslContext = SSLContext.getInstance("TLS");
        sslContext.init(kmf.getKeyManagers(), new TrustManager[]{}, null);

       server.setHttpsConfigurator(new HttpsConfigurator(sslContext) {
           public void configure (HttpsParameters params) {

               // get the remote address if needed
               InetSocketAddress remote = params.getClientAddress();

               SSLContext c = getSSLContext();

               // get the default parameters
               SSLParameters sslparams = c.getDefaultSSLParameters();

               params.setSSLParameters(sslparams);
               // statement above could throw IAE if any params invalid.
               // eg. if app has a UI and parameters supplied by a user.

           }
       });

        ExecutorService executor = Executors.newFixedThreadPool(5);
        server.setExecutor(executor); // creates a default executor
        server.start();
        executor.awaitTermination(Integer.MAX_VALUE, TimeUnit.DAYS);

    }

    void startServer(int port) throws IOException, KeyStoreException, CertificateException, NoSuchAlgorithmException,
                                      UnrecoverableKeyException, InterruptedException, KeyManagementException {
        HttpsServer server = HttpsServer.create(new InetSocketAddress(port), 5);
        server.createContext("/", new MyHandler());

        char[] storepass = "storepass".toCharArray();
        char[] keypass = "serverpass".toCharArray();

        KeyStore ks = KeyStore.getInstance("JKS");
        ks.load(SimpleServerTest.class.getResourceAsStream("server.jks"), storepass);

        KeyManagerFactory kmf = KeyManagerFactory.getInstance("SunX509");
        kmf.init(ks, keypass);

        SSLContext sslContext = SSLContext.getInstance("TLS");
        sslContext.init(kmf.getKeyManagers(), new TrustManager[]{}, null);

        server.setHttpsConfigurator(new HttpsConfigurator(sslContext) {
            public void configure (HttpsParameters params) {

                // get the remote address if needed
                InetSocketAddress remote = params.getClientAddress();

                SSLContext c = getSSLContext();

                // get the default parameters
                SSLParameters sslparams = c.getDefaultSSLParameters();

                params.setSSLParameters(sslparams);
                // statement above could throw IAE if any params invalid.
                // eg. if app has a UI and parameters supplied by a user.

            }
        });
        server.setExecutor(null); // creates a default executor
        server.start();
    }

    void startServerWithTruststore(int port) throws IOException, KeyStoreException, CertificateException, NoSuchAlgorithmException,
                                      UnrecoverableKeyException, InterruptedException, KeyManagementException {
        HttpsServer server = HttpsServer.create(new InetSocketAddress(port), 5);
        server.createContext("/", new MyHandler());

        char[] storepass = "storepass".toCharArray();
        char[] keypass = "serverpass".toCharArray();

        KeyStore ks = KeyStore.getInstance("JKS");
        ks.load(SimpleServerTest.class.getResourceAsStream("server.jks"), storepass);

        KeyManagerFactory kmf = KeyManagerFactory.getInstance("SunX509");
        kmf.init(ks, keypass);

        KeyStore ts = KeyStore.getInstance("JKS");
        ts.load(this.getClass().getResourceAsStream("servertrust.jks"), storepass);
        TrustManagerFactory tmf = TrustManagerFactory.getInstance("SunX509");
        tmf.init(ts);

        SSLContext sslContext = SSLContext.getInstance("TLS");
        sslContext.init(kmf.getKeyManagers(), tmf.getTrustManagers(), null);

        server.setHttpsConfigurator(new HttpsConfigurator(sslContext) {
            public void configure (HttpsParameters params) {

                // get the remote address if needed
                //InetSocketAddress remote = params.getClientAddress();

                //SSLContext c = getSSLContext();

                // get the default parameters
                //SSLParameters sslparams = c.getDefaultSSLParameters();

                //params.setSSLParameters(null);
                params.setWantClientAuth(true);
                params.setNeedClientAuth(true);
                // statement above could throw IAE if any params invalid.
                // eg. if app has a UI and parameters supplied by a user.

            }
        });
        server.setExecutor(null); // creates a default executor
        server.start();
    }


    @Test
    public void testSimpleHttpsClient()
        throws CertificateException, InterruptedException, UnrecoverableKeyException, NoSuchAlgorithmException,
               IOException, KeyManagementException, KeyStoreException {

        startServer(8000);

        URL url = new URL("https://localhost:8000/");

        HttpsURLConnection con = (HttpsURLConnection)url.openConnection();
        con.setRequestMethod( "GET" );

        SSLContext sslContext = SSLContext.getInstance("TLS");

        sslContext.init(null, null, null);
        con.setSSLSocketFactory(sslContext.getSocketFactory());

        int responseCode = con.getResponseCode();
        InputStream inputStream;
        if (responseCode == HttpURLConnection.HTTP_OK) {
            inputStream = con.getInputStream();
        } else {
            inputStream = con.getErrorStream();
        }

        // Process the response
        BufferedReader reader;
        String line = null;
        reader = new BufferedReader( new InputStreamReader( inputStream ) );
        while( ( line = reader.readLine() ) != null )
        {
            System.out.println( line );
        }

        inputStream.close();
    }

    @Test
    public void testSimpleHttpsClientWithTrustManagerAndVerifier()
        throws CertificateException, InterruptedException, UnrecoverableKeyException, NoSuchAlgorithmException,
               IOException, KeyManagementException, KeyStoreException {

        startServer(8000);

        URL url = new URL("https://localhost:8000/");

        HttpsURLConnection con = (HttpsURLConnection)url.openConnection();
        con.setRequestMethod( "GET" );

        SSLContext sslContext = SSLContext.getInstance("TLS");

        TrustManager[] trustManagers = new TrustManager[] {
            new X509TrustManager() {

                public java.security.cert.X509Certificate[] getAcceptedIssuers() {
                    return null;
                }

                public void checkClientTrusted(X509Certificate[] certs, String authType) {  }

                public void checkServerTrusted(X509Certificate[] certs, String authType) {  }

            }
        };
        HostnameVerifier hostnameVerifier = new HostnameVerifier() {
            @Override
            public boolean verify(String s, SSLSession sslSession) {
                return s.equals(sslSession.getPeerHost());
            }
        };
        con.setHostnameVerifier(hostnameVerifier);


        sslContext.init(null, trustManagers, null);
        con.setSSLSocketFactory(sslContext.getSocketFactory());


        int responseCode = con.getResponseCode();
        InputStream inputStream;
        if (responseCode == HttpURLConnection.HTTP_OK) {
            inputStream = con.getInputStream();
        } else {
            inputStream = con.getErrorStream();
        }

        // Process the response
        BufferedReader reader;
        String line = null;
        reader = new BufferedReader( new InputStreamReader( inputStream ) );
        while( ( line = reader.readLine() ) != null )
        {
            System.out.println( line );
        }

        inputStream.close();
    }

    @Test
    public void testClientWithTrustStore()
        throws CertificateException, InterruptedException, UnrecoverableKeyException, NoSuchAlgorithmException,
               IOException, KeyManagementException, KeyStoreException {

        startServer(8000);

        URL url = new URL("https://localhost:8000/");

        HttpsURLConnection con = (HttpsURLConnection)url.openConnection();
        con.setRequestMethod( "GET" );

        SSLContext sslContext = SSLContext.getInstance("TLS");

        char[]  passphrase = "storepass".toCharArray();
        KeyStore ks = KeyStore.getInstance("JKS");
        ks.load(this.getClass().getResourceAsStream("clienttrust.jks"), passphrase);
        TrustManagerFactory tmf = TrustManagerFactory.getInstance("SunX509");
        tmf.init(ks);

        HostnameVerifier hostnameVerifier = new HostnameVerifier() {
            @Override
            public boolean verify(String s, SSLSession sslSession) {
                return s.equals(sslSession.getPeerHost());
            }
        };
        con.setHostnameVerifier(hostnameVerifier);


        sslContext.init(null, tmf.getTrustManagers(), null);
        con.setSSLSocketFactory(sslContext.getSocketFactory());


        int responseCode = con.getResponseCode();
        InputStream inputStream;
        if (responseCode == HttpURLConnection.HTTP_OK) {
            inputStream = con.getInputStream();
        } else {
            inputStream = con.getErrorStream();
        }

        // Process the response
        BufferedReader reader;
        String line = null;
        reader = new BufferedReader( new InputStreamReader( inputStream ) );
        while( ( line = reader.readLine() ) != null )
        {
            System.out.println( line );
        }

        inputStream.close();
    }

    @Test
    public void testTwoWayAuthentication()
        throws CertificateException, InterruptedException, UnrecoverableKeyException, NoSuchAlgorithmException,
               IOException, KeyManagementException, KeyStoreException {

        startServerWithTruststore(8000);

        URL url = new URL("https://localhost:8000/");

        HttpsURLConnection con = (HttpsURLConnection)url.openConnection();
        con.setRequestMethod( "GET" );

        SSLContext sslContext = SSLContext.getInstance("TLS");

        char[]  passphrase = "storepass".toCharArray();
        char[]  keypass = "serverpass".toCharArray();

        KeyStore ks = KeyStore.getInstance("JKS");
        ks.load(SimpleServerTest.class.getResourceAsStream("client.jks"), passphrase);

        KeyManagerFactory kmf = KeyManagerFactory.getInstance("SunX509");
        kmf.init(ks, keypass);

        KeyStore ts = KeyStore.getInstance("JKS");
        ts.load(this.getClass().getResourceAsStream("clienttrust.jks"), passphrase);
        TrustManagerFactory tmf = TrustManagerFactory.getInstance("SunX509");
        tmf.init(ts);

        HostnameVerifier hostnameVerifier = new HostnameVerifier() {
            @Override
            public boolean verify(String s, SSLSession sslSession) {
                return s.equals(sslSession.getPeerHost());
            }
        };
        con.setHostnameVerifier(hostnameVerifier);


        sslContext.init(kmf.getKeyManagers(), tmf.getTrustManagers(), null);
        con.setSSLSocketFactory(sslContext.getSocketFactory());


        int responseCode = con.getResponseCode();
        InputStream inputStream;
        if (responseCode == HttpURLConnection.HTTP_OK) {
            inputStream = con.getInputStream();
        } else {
            inputStream = con.getErrorStream();
        }

        // Process the response
        BufferedReader reader;
        String line = null;
        reader = new BufferedReader( new InputStreamReader( inputStream ) );
        while( ( line = reader.readLine() ) != null )
        {
            System.out.println( line );
        }

        inputStream.close();
    }




}
