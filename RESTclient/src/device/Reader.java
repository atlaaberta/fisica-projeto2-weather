package device;

import dao.DBManager;

public class Reader extends Thread {
	
	private boolean status = false;
	private String greatness = "analog";
	private RequestJson requester;
	private DBManager databaseManager;
	
	

	public Reader(String address) {
		this.requester = new RequestJson(address);
		this.status = true;
		this.databaseManager = new DBManager();
	}
	
	@Override
	public void run() {
		databaseManager.getConnection();
		databaseManager.createTable();
		
		while(status) {
			//String s = requester.getDeviceValue(greatness);
			String s = requester.getWeather();
			databaseManager.insertValue(s);
			//System.out.println("Current value: " + requester.getDeviceValue(greatness));
			try {
				Thread.sleep(10000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	public void setGreatness(String greatness) {
		this.greatness = greatness;
	}
	
	public DBManager getDatabaseManager() {
		return databaseManager;
	}

}
