package org.mccakit.app;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import org.json.JSONArray;
import org.json.JSONObject;
import org.json.JSONException;
import java.io.IOException;
import java.io.InputStream;
import java.io.ByteArrayOutputStream;
import java.util.Set;
import java.util.UUID;

public class Bt {
    private BluetoothAdapter bluetoothAdapter;
    private Context context;
    private static Bt instance;
    private BluetoothSocket bluetoothSocket;
    private InputStream inputStream;
    private ByteArrayOutputStream buffer = new ByteArrayOutputStream();

    // Standard Serial Port Profile UUID for Classic Bluetooth
    private static final UUID SPP_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    public Bt(Context context) {
        this.context = context;
        this.bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
    }

    /**
     * Create or get singleton instance
     */
    public static Bt getInstance(Context context) {
        if (instance == null) {
            instance = new Bt(context);
        }
        return instance;
    }

    /**
     * Get all paired Bluetooth devices in JSON format
     * @return JSON string with format: {"devices": [{"name": "...", "address": "..."}, ...]}
     */
    public String getPairedDevices() {
        JSONObject result = new JSONObject();
        JSONArray devicesArray = new JSONArray();

        try {
            if (bluetoothAdapter == null) {
                result.put("error", "Bluetooth adapter not available");
                return result.toString();
            }

            Set<BluetoothDevice> pairedDevices = bluetoothAdapter.getBondedDevices();

            if (pairedDevices != null && pairedDevices.size() > 0) {
                for (BluetoothDevice device : pairedDevices) {
                    JSONObject deviceObj = new JSONObject();
                    deviceObj.put("name", device.getName());
                    deviceObj.put("address", device.getAddress());
                    deviceObj.put("type", device.getType());
                    devicesArray.put(deviceObj);
                }
            }

            result.put("devices", devicesArray);
            result.put("status", "success");
        } catch (JSONException e) {
            try {
                result.put("error", e.getMessage());
            } catch (JSONException ex) {
                ex.printStackTrace();
            }
        }

        return result.toString();
    }

    /**
     * Check if Bluetooth is enabled
     * @return true if Bluetooth is enabled, false otherwise
     */
    public boolean isBluetoothEnabled() {
        return bluetoothAdapter != null && bluetoothAdapter.isEnabled();
    }

    /**
     * Get local Bluetooth adapter name
     * @return Bluetooth device name
     */
    public String getLocalDeviceName() {
        if (bluetoothAdapter != null) {
            return bluetoothAdapter.getName();
        }
        return "Unknown";
    }

    /**
     * Get local Bluetooth adapter address
     * @return Bluetooth MAC address
     */
    public String getLocalDeviceAddress() {
        if (bluetoothAdapter != null) {
            return bluetoothAdapter.getAddress();
        }
        return "00:00:00:00:00:00";
    }

    /**
     * Connect to a Classic Bluetooth device using its MAC address
     * @param macAddress The MAC address of the device (e.g., "AA:BB:CC:DD:EE:FF")
     * @return true if connection successful, false otherwise
     * @throws IOException if connection fails
     * @throws IllegalArgumentException if MAC address is invalid
     */
    public boolean connectToDevice(String macAddress) throws IOException {
        if (bluetoothAdapter == null) {
            throw new IOException("Bluetooth adapter not available");
        }

        if (!bluetoothAdapter.isEnabled()) {
            throw new IOException("Bluetooth is not enabled");
        }

        // Disconnect existing connection if any
        if (bluetoothSocket != null && bluetoothSocket.isConnected()) {
            bluetoothSocket.close();
        }

        // Get the remote device
        BluetoothDevice device = bluetoothAdapter.getRemoteDevice(macAddress);

        // Cancel discovery to improve connection speed
        if (bluetoothAdapter.isDiscovering()) {
            bluetoothAdapter.cancelDiscovery();
        }

        // Create socket and connect
        bluetoothSocket = device.createRfcommSocketToServiceRecord(SPP_UUID);
        bluetoothSocket.connect();

        // Initialize input stream
        if (bluetoothSocket.isConnected()) {
            inputStream = bluetoothSocket.getInputStream();
        }

        return bluetoothSocket.isConnected();
    }

    /**
     * Disconnect from the currently connected device
     */
    public void disconnect() {
        try {
            if (inputStream != null) {
                inputStream.close();
                inputStream = null;
            }
            if (bluetoothSocket != null) {
                bluetoothSocket.close();
                bluetoothSocket = null;
            }
            buffer.reset();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Check if currently connected to a device
     * @return true if connected, false otherwise
     */
    public boolean isConnected() {
        return bluetoothSocket != null && bluetoothSocket.isConnected();
    }

    /**
     * Get the socket for data transmission (if you need to send/receive data)
     * @return BluetoothSocket or null if not connected
     */
    public BluetoothSocket getSocket() {
        return bluetoothSocket;
    }

    /**
     * Read all available data from the Bluetooth input stream and return it
     * The internal buffer is cleared after reading
     * @return String containing all data read from the device, or empty string if no data
     * @throws IOException if reading fails or not connected
     */
    public String readBuffer() throws IOException {
        if (bluetoothSocket == null || !bluetoothSocket.isConnected()) {
            throw new IOException("Not connected to any device");
        }

        if (inputStream == null) {
            inputStream = bluetoothSocket.getInputStream();
        }

        // Read all available bytes
        int available = inputStream.available();
        if (available > 0) {
            byte[] bytes = new byte[available];
            int bytesRead = inputStream.read(bytes);
            buffer.write(bytes, 0, bytesRead);
        }

        // Get the buffer content as string
        String result = buffer.toString("UTF-8");

        // Clear the buffer
        buffer.reset();

        return result;
    }

    /**
     * Read buffer and return as byte array instead of string
     * @return byte array containing all data, or empty array if no data
     * @throws IOException if reading fails or not connected
     */
    public byte[] readBufferBytes() throws IOException {
        if (bluetoothSocket == null || !bluetoothSocket.isConnected()) {
            throw new IOException("Not connected to any device");
        }

        if (inputStream == null) {
            inputStream = bluetoothSocket.getInputStream();
        }

        int available = inputStream.available();
        if (available > 0) {
            byte[] bytes = new byte[available];
            int bytesRead = inputStream.read(bytes);
            buffer.write(bytes, 0, bytesRead);
        }

        byte[] result = buffer.toByteArray();
        buffer.reset();

        return result;
    }
}
