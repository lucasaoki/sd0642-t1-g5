import java.net.*;
import java.io.*;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

/**
 * @author Gilberto Volpe Neto, Lucas Aoki Heredia, Rafael Seiji Ishibe
 * This class is a Clientfor teste connections with server in JAVA/C/C++	
 */
public class Client {

	/**
	 * Constructor receive ip(String), port(int)
	 * and create a socket client in java
	 * Create two Array, one to send 125 int to put in Order
	 * another to receive 1000 int in order
	 * */
	public Client(String ip, int port) throws IOException {
		clientPort = port;
		client = new Socket(ip, clientPort);

		Array = new Integer[SIZE];
		ArrayFinal = new Integer[8 * SIZE];
	}

	/**
	 * Insert 125 int in Array 
	 * In Random form 
	 * */
	public void randomArray() {
		for (int i = 0; i < SIZE; i++) {
			Array[i] = 1 + (int) (Math.random() * NUM);
		}
	}

	/**
	 * Show a array of size, one elem by line
	 * */	
	public void printArray(Integer Array[], int size) {
		for (int i = 0; i < size; i++) {
			System.out.printf("%d %d\n", i, Array[i]);
		}
	}

	/**
	 * Do the work, send 125 ints to server, and
	 * wait for 1000 ints
	 * For send is necessary convert the order byte
	 * BigEndian -> LittleEndian
	 * When receive data is unecessary convert because
	 * java to the work
	 * */
	public void doWork() throws IOException {

		OutputStream out = client.getOutputStream();
		
		byte send[] = new byte[SIZE * 4];
		ByteBuffer buffer = ByteBuffer.allocate(SIZE * 4);
		buffer.order(ByteOrder.LITTLE_ENDIAN);

		int value;
		for (int k = 0, j = 0; k < SIZE; k++, j += 4) {

			value = Array[k].intValue();
			buffer.putInt(value);

			for (int i = 0; i < 4; i++) {
				send[j + i] = buffer.get(j + i);
			}
		}
		
		double sendArray = System.currentTimeMillis();
		out.write(send);
		
		InputStream in = client.getInputStream();
		byte recv[] = new byte[SIZE * 32];

		int numberRead = in.read(recv);
		
		while( numberRead < 2000){
			recv[numberRead] = (byte) in.read();
			numberRead++;
		}
		
		double recvArray = System.currentTimeMillis();
		
		ByteBuffer bufferres = ByteBuffer.allocate(SIZE * 32);
		bufferres.order(ByteOrder.LITTLE_ENDIAN);
		bufferres.put(recv);

		for (int j = 0, k = 0; k < 8 * SIZE; j += 4, k++) {
			ArrayFinal[k] = bufferres.getInt(j);
		}
		
		comunicationTime = (recvArray - sendArray)/1000; 
		client.close();
		out.close();
		in.close();
	}
	
	public void setTimeTotal(double start,double end){
		totalTime = (end - start)/1000;
	}

	public String toString(){
		
		String text = "";
		text += "Total time for ordering" + totalTime + "\n";
		text += "Time for communication" + comunicationTime + "\n";
		
		text+= "Array in Order: \n";
		for (int i = 0; i < ArrayFinal.length; i++){
			text += Integer.toString(ArrayFinal[i].intValue()) + " ";
			if( i != 0 && (i%10) == 0)
				text += "\n";
		}
		
		return text;
	}
	
	public static void main(String[] args) throws IOException {
		
		if( args.length < 2 )
			System.out.println("The arguments are: ipServer portCommunication\n"); 
		else{
			Client client = new Client(args[0], Integer.parseInt(args[1]));
			
			double startTimeTotal = System.currentTimeMillis();
			client.randomArray();
		
			client.doWork();
			double finalTimeTotal = System.currentTimeMillis();
			
			client.setTimeTotal(startTimeTotal, finalTimeTotal);
			
			System.out.println(client);
		}
	}

	public static final int SIZE = 125;
	public static final int NUM = 9999;
	private Socket client;
	private int clientPort;
	private Integer Array[];
	private Integer ArrayFinal[];
	private double totalTime;
	private double comunicationTime;
}
