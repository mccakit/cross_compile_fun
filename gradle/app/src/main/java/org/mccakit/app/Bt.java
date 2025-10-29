package org.mccakit.app;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import org.json.JSONArray;
import org.json.JSONObject;
import org.json.JSONException;
import java.util.Set;

public class Bt {
    private BluetoothAdapter bluetoothAdapter;
    private Context context;
    private static Bt instance;

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
}
