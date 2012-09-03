package servermain.grupo05sd;

import java.io.IOException;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

/**
 * @author Gilberto Volpe Neto, Lucas Aoki Heredia, Rafael Seiji Ishibe
 * This class is a Server for teste connections with clients in C/C++
 * for android	
 */
public class MainActivity extends Activity implements Utilites, Runnable {
	
	/**
	 * 	This method is call when the App on Android is started
	 *  Start a Thread to check with the server finish work
	 * */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		try {
			server = new ServerMain(42000);
			Thread t = new Thread(this);
			t.start();

			work = false;
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		setContentView(R.layout.activity_main);
	}

	
	/**
	 * Called when the user clicks the Send button
	 * If The value on the EditText is higher than 1024
	 * than start the server
	 * else show a message to user in TextView
	 * @throws IOException
	 */
	public void startServer(View view) throws IOException {

		// Do something in response to button
		EditText myEdit = (EditText) findViewById(R.id.edit_message);
		
		
		if( myEdit.getText() != null)
			port = Integer.parseInt(myEdit.getText().toString());
		else
			port = 0;
		
		TextView myView = (TextView) findViewById(R.id.text_message);

		if (port > 1024) {
			if (work == false) {
				myView.setText("Start the server\n");
				server.setPort(port);
				Thread t = new Thread(server);
				t.start();
				work = true;
			}
		} else {
			myView.setText("Port must be higher than 1024");
		}
	}
	
	/**
	 * This method is called by a thread for 
	 * check with server finish, with finish
	 * than show the time spend on 
	 * Ordinate the Array
	 * */
	@Override
	public void run() {

		try {
			while (server.finishWork() == false)
				Thread.sleep(100);
			threadHandler.sendEmptyMessage(0);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	/**
	 * Method with interpretated the message come from
	 * a thread, and show this on TextView. 
	 * */	
	 private Handler threadHandler = new Handler() {
		public void handleMessage(android.os.Message msg) {
			TextView myView = (TextView) findViewById(R.id.text_message);
			myView.setText(server.toString());
		}
	};
	
	private ServerMain server;
	private int port;
	private boolean work;
}
