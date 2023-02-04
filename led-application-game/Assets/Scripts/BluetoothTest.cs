using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class BluetoothTest : MonoBehaviour
{
    //public Text deviceName;
    [SerializeField] public TMPro.TMP_InputField inputArea;
    private bool IsConnected;
    public static string dataRecived = "";
    // Start is called before the first frame update
    void Start()
    {
        IsConnected = false;
        BluetoothService.CreateBluetoothObject();
       
    }

    // Update is called once per frame
    void Update()
    {
        if (IsConnected) {
            try
            {
               string datain =  BluetoothService.ReadFromBluetooth();
                if (datain.Length > 1)
                {
                    dataRecived = datain;
                    print(dataRecived);
                }

            }
            catch (Exception e)
            {

            }
        }
        
    }

    public void StartButton()
    {
        if (!IsConnected)
        {
            print("ESP32 Badge");
            IsConnected =  BluetoothService.StartBluetoothConnection("ESP32 Badge");
        }
    }

    public void SendButton()
    {
        if (IsConnected && (inputArea.ToString() != "" || inputArea.ToString() != null))
        {
            BluetoothService.WritetoBluetooth(inputArea.text.ToString());
        }
    }


    public void StopButton()
    {
        if (IsConnected)
        {
            BluetoothService.StopBluetoothConnection();
        }
        Application.Quit();
    }
}
