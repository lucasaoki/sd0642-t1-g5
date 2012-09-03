package servermain.grupo05sd;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

/**
 * @author Gilberto Volpe Neto, Lucas Aoki Heredia, Rafael Seiji Ishibe This
 *         class is a Server for teste connections with clients in C/C++
 */
public class ServerMain implements Utilites, Runnable {

	/**
	 * Constructor receives a int(the port) Create two Arrays the one to receive
	 * datas another to receive the Array in Order
	 * */
	ServerMain(int serverPort) throws IOException {
		this.serverPort = serverPort;

		ArrayFinal = new Integer[SIZE * 8];
		FirstArray = new Integer[SIZE * 8];
		finish = false;

		for (int i = 0; i < FirstArray.length; i++) {
			FirstArray[i] = 0;
			ArrayFinal[i] = 0;
		}
	}

	/**
	 * Check to see if server work is finish
	 * */
	boolean finishWork() {
		return finish;
	}

	/**
	 * Set the port in Server, before doWork is called.
	 * */
	public void setPort(int port) {
		this.serverPort = port;
	}

	/**
	 * Return the time spend to put array in order
	 * */
	public String toString() {

		String number = "Time for Order the Array: " + timeExec + "s\n";
		number += "Array in Order: \n";
		for (int i = 0; i < ArrayFinal.length; i++)
			number += Integer.toString(ArrayFinal[i].intValue()) + " ";

		return number;
	}

	/**
	 * Do the work in server, accept two connections read data from client,
	 * ordering the array and send to client the array in order
	 * */
	public void doWork() throws IOException {

		this.server = new ServerSocket(this.serverPort);

		Socket socket[] = new Socket[NUM_MAX_CONNECTIONS];

		for (int i = 0; i < NUM_MAX_CONNECTIONS; i++)
			socket[i] = server.accept();

		readSocket(socket[0], 0);
		readSocket(socket[1], 500);

		for (int i = 0; i < FirstArray.length; i++)
			ArrayFinal[i] = FirstArray[i];

		double startTime = System.currentTimeMillis();
		bubbleSort(ArrayFinal, SIZE * 8);
		double finalTime = System.currentTimeMillis();

		timeExec = (finalTime - startTime) / 1000;

		for (int i = 0; i < NUM_MAX_CONNECTIONS; i++) {
			sendSocket(socket[i]);
			socket[i].close();
		}

		server.close();
		finish = true;
	}

	/**
	 * To send data to C/C++ client is necessary convert the byte order of int
	 * BigEndian -> LittleEndian
	 * */
	private synchronized void sendSocket(Socket sock) throws IOException {

		OutputStream out = sock.getOutputStream();
		byte send[] = new byte[SIZE * 32];

		ByteBuffer buffer = ByteBuffer.allocate(SIZE * 32);
		buffer.order(ByteOrder.LITTLE_ENDIAN);

		int value;
		for (int k = 0, j = 0; k < 8 * SIZE; k++, j += 4) {

			value = ArrayFinal[k].intValue();
			buffer.putInt(value);

			for (int i = 0; i < 4; i++) {
				send[j + i] = buffer.get(j + i);
			}
		}

		out.write(send);
	}

	/**
	 * To receive data from C/C++ client is necessary convert the byte order of
	 * int LittleEndian -> BigEndian
	 * */
	private synchronized void readSocket(Socket sock, int index)
			throws IOException {

		byte recv[] = new byte[SIZE * 16];
		InputStream in = sock.getInputStream();

		int numberRead = in.read(recv);
		
		if( numberRead < 2000){
			int i = numberRead;
			while( i<2000){
				recv[i] = (byte) in.read();
				i++;
			}
		}
		
		ByteBuffer bufferres = ByteBuffer.allocate(SIZE * 16);

		bufferres.order(ByteOrder.LITTLE_ENDIAN);
		bufferres.put(recv);

		int step = (4 * SIZE + index);
		for (int j = 0, k = index; k < step; j += 4, k++) {
			FirstArray[k] = bufferres.getInt(j);
		}
	}

	/**
	 * The Famous BubbleSort
	 * */
	public void bubbleSort(Integer Array[], int size) {
		int i, j;
		Integer swap;
		for (i = 0; i < size; i++) {
			for (j = 0; j < size - 1; j++) {
				if (Array[j] > Array[j + 1]) {
					swap = Array[j];
					Array[j] = Array[j + 1];
					Array[j + 1] = swap;
				}
			}
		}
	}

	/**
	 * The method called by Thread really work in server.
	 * */
	@Override
	public void run() {
		// TODO Auto-generated method stub
		try {
			doWork();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public static final int NUM_MAX_CONNECTIONS = 2;

	private ServerSocket server;
	private int serverPort;
	private Integer ArrayFinal[];
	private Integer FirstArray[];
	private boolean finish;
	private double timeExec;

	private static final int NUM_BYTES = 2000;
}
