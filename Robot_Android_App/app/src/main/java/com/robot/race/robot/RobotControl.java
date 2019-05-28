package com.robot.race.robot;

import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Handler;
import android.support.v7.app.ActionBar;
import android.support.v7.app.ActionBarActivity;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.util.UUID;

public class RobotControl extends ActionBarActivity {
    private TextView logview;
    private Button  disconnect;
    String address = null;
    private ProgressDialog progress;
    private ImageView forwardArrow, backArrow, rightArrow, leftArrow, stop;
    private BluetoothAdapter myBluetooth = null;
    BluetoothSocket btSocket = null;
    private boolean isBtConnected = false;
    private String[] logArray = null;
    //SPP UUID. Look for it
    static final UUID myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_robot_control);
        Intent newint = getIntent();
        address = newint.getStringExtra(RobotActivity.EXTRA_ADDRESS); //receive the address of the bluetooth device

        logview = (TextView)findViewById(R.id.logview);
        //I chose to display only the last 3 messages
        logArray = new String[3];
        disconnect = (Button)findViewById(R.id.disconnect);
        forwardArrow = (ImageView)findViewById(R.id.forward_arrow);
        backArrow = (ImageView)findViewById(R.id.back_arrow);
        rightArrow = (ImageView)findViewById(R.id.right_arrow);
        leftArrow = (ImageView)findViewById(R.id.left_arrow);
        stop = (ImageView)findViewById(R.id.stop);
        new ConnectBT().execute(); //Call the class to connect

        forwardArrow.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                forwardArrow();      //method to turn forward robot
            }

            private void forwardArrow() {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("F".toString().getBytes());
                        addToLog("Moving Forward");
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });
        backArrow.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                backArrow();      //method to turn backward robot
            }

            private void backArrow() {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("B".toString().getBytes());
                        addToLog("Moving Backward");
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });
        rightArrow.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                rightArrow();      //method to turn right robot
            }

            private void rightArrow() {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("L".toString().getBytes());
                        addToLog("Moving Right");
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });
        leftArrow.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                leftArrow();      //method to turn left robot
            }

            private void leftArrow() {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("R".toString().getBytes());
                        addToLog("Moving Left");
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });
        stop.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                stop();      //method to stop Robot
            }

            private void stop() {
                if (btSocket!=null)
                {
                    try
                    {
                        btSocket.getOutputStream().write("S".toString().getBytes());
                        addToLog("Stopping");
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });
        disconnect.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                disconnect();      //method to stop Robot
            }

            private void disconnect() {
                if (btSocket!=null) //If the btSocket is busy
                {
                    try
                    {
                        btSocket.close(); //close connection
                    }
                    catch (IOException e)
                    { msg("Error");}
                }
                finish(); //return to the first layout

            }
        });




    }
    private class ConnectBT extends AsyncTask<Void, Void, Void>  // UI thread
    {
        private boolean ConnectSuccess = true; //if it's here, it's almost connected

        @Override
        protected void onPreExecute()
        {
            progress = ProgressDialog.show(RobotControl.this, "Connecting...", "Please wait!!!");  //show a progress dialog
        }

        @Override
        protected Void doInBackground(Void... devices) //while the progress dialog is shown, the connection is done in background
        {
            try
            {
                if (btSocket == null || !isBtConnected)
                {
                    myBluetooth = BluetoothAdapter.getDefaultAdapter();//get the mobile bluetooth device
                    BluetoothDevice dispositivo = myBluetooth.getRemoteDevice(address);//connects to the device's address and checks if it's available
                    btSocket = dispositivo.createInsecureRfcommSocketToServiceRecord(myUUID);//create a RFCOMM (SPP) connection
                    BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                    btSocket.connect();//start connection
                }
            }
            catch (IOException e)
            {
                ConnectSuccess = false;//if the try failed, you can check the exception here
            }
            return null;
        }
        @Override
        protected void onPostExecute(Void result) //after the doInBackground, it checks if everything went fine
        {
            super.onPostExecute(result);

            if (!ConnectSuccess)
            {
                msg("Connection Failed. Is it a SPP Bluetooth? Try again.");
                finish();
            }
            else
            {
                msg("Connected.");
                isBtConnected = true;
            }
            progress.dismiss();
        }
    }
    // fast way to call Toast
    private void msg(String s)
    {
        Toast.makeText(getApplicationContext(),s,Toast.LENGTH_LONG).show();
    }
    private void addToLog(String message){
        for (int i = 1; i < logArray.length; i++){
            logArray[i-1] = logArray[i];
        }
        logArray[logArray.length - 1] = message;

        logview.setText("");
        for (int i = 0; i < logArray.length; i++){
            if (logArray[i] != null){
                logview.append(logArray[i] + "\n");
            }
        }
    }
    private Boolean exit = false;
    @Override
    public void onBackPressed() {
        if (exit) {
            if (btSocket!=null) //If the btSocket is busy
            {
                try
                {
                    btSocket.close(); //close connection
                }
                catch (IOException e)
                { msg("Error");}
            }
            // bt.close();
            finish(); // finish activity
        } else {
            Toast.makeText(this, "Press Back again to Exit.",
                    Toast.LENGTH_SHORT).show();
            exit = true;
            new Handler().postDelayed(new Runnable() {
                @Override
                public void run() {
                    exit = false;
                }
            }, 3 * 1000);

        }

    }
}
