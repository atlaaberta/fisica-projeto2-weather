package device;

import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.UriBuilder;
import com.sun.jersey.api.client.Client;
import com.sun.jersey.api.client.WebResource;
import com.sun.jersey.api.client.config.ClientConfig;
import com.sun.jersey.api.client.config.DefaultClientConfig;

public class RequestJson {
	private ClientConfig config = new DefaultClientConfig();
	private Client client = Client.create(config);
	private String address = "";
	
	public RequestJson(String address) {
		this.address = address;
	}
	
	public String getDeviceValue(String greatness) {
		WebResource service = client.resource(UriBuilder.fromUri("http://" + address + "/" + greatness + "/1").build());
		return service.path("restPath").path("resourcePath").accept(MediaType.APPLICATION_JSON).get(String.class);
	}
	
	public String getWeather() {
		WebResource service = client.resource(UriBuilder.fromUri("http://" + address).build());
		return service.path("restPath").path("resourcePath").accept(MediaType.APPLICATION_JSON).get(String.class);
	}

	public void  pinSwitch(String greatness, int pinEsp, String state) {
		WebResource service = client.resource(UriBuilder.fromUri("http://" + address + "/" + greatness + "/" + pinEsp + "/" + state).build());
		System.out.println(service.path("restPath").path("resourcePath").accept(MediaType.APPLICATION_JSON).get(String.class));
	}

}
