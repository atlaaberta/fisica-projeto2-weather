package main;

import java.util.Scanner;

import device.Reader;
import device.RequestJson;

public class Main {
	
	public static void main(String[] args) {
		
		int op = 0;
		String address = "192.168.137.26";
		
		
		Scanner scanner = new Scanner(System.in);
		RequestJson requester = new RequestJson(address);
		
		//System.out.println("PIN 1 como input (MICROFONE)");
		//requester.pinSwitch("mode", 1, "i");
		
		System.out.println("PIN D1 como output (LED)");
		int pinLed = 1;
		requester.pinSwitch("mode", 1, "o");
		
		Reader reader = new Reader(address);
		reader.start();
		
		System.out.println("Banco de dados iniciado...");
		System.out.println("Coleta iniciada...");
		
		do {
			System.out.println("(1) Ligar o led");
			System.out.println("(2) Desligar o led");
			System.out.println("(3) Ler dispositivo");
			System.out.println("(4) Ler banco de dados");
			System.out.println("(5) Mudar grandeza");
			System.out.println("Informe uma opção:");
			
			op = scanner.nextInt();
			String greatness = "digital";
			switch (op) {
			case 1:
				System.out.print("Pin: ");
				requester.pinSwitch(greatness, pinLed, "1");
				break;
				
			case 2:
				System.out.print("Pin: ");
				requester.pinSwitch(greatness, pinLed, "0");
				break;
				
			case 3:
				System.out.print("Current value: ");
				String current = requester.getDeviceValue(greatness);
				System.out.println(current);
				break;
				
			case 4:
				reader.getDatabaseManager().readValues();
				break;
				
			case 5:
				greatness = scanner.next();
				reader.setGreatness(greatness);
				break;


			default:
				break;
			}
		} while(op != 10);
		scanner.close();
	}
}
