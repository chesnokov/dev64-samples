<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
	pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
		<title>Plugin tester</title>
	</head>
	
	<body>
		<h1>Servlet Parameters demo</h1>
		
		<form action = "servlet-parameters" method = "GET">
		
		<table border = "0">
			
			<tr>
				<td><b>Parameter1</b></td>
				<td><input type = "text" name = "parameter1" value = "http://localhost/some-test-url" size = "70"/></td>
			</tr>
			
			<tr>
				<td><b>Parameter2</b></td>
				<td><input type = "text" name = "parameter2" value = "001" size = "65"/></td>
			</tr>
			

			<tr>
				<td>Parameter choice</td>
				<td>
					<select name = "possible-result">
						<option value = "">Success</option>
						<option value = "ERR-500">ERR-500 Technical error</option>
						<option value = "ERR-1003">ERR-1003 Requested information is not available</option>
						<option value = "ERR-1005">ERR-1005 Some other Error</option>
					</select>
				</td>
			</tr>
			
			<tr>
				<td colspan = "2"><input type = "submit" value = "Start test"/></td>
			</tr>
		</table>
		</form>
	</body>
</html>