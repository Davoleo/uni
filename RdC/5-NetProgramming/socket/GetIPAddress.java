import java.net.*;
import java.io.*;

public class GetIPAddress
{
	public static void main(String[] args) throws IOException, UnknownHostException
	{
		InetAddress mysite = InetAddress.getByName("starwave.com");
		InetAddress local = InetAddress.getLocalHost();
		InetAddress addr = InetAddress.getByName("160.78.48.10");
		
		System.out.println(mysite);
		System.out.println(local);
		System.out.println(addr);
				
		System.out.println(mysite.getHostAddress());
		System.out.println(local.getHostName());
 	}
}

