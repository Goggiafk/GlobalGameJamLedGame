using System.Collections;
using System.Collections.Generic;
using Uduino;
using UnityEngine;

public class SetIP : MonoBehaviour
{
    [SerializeField] private TMPro.TMP_InputField inputArea;
    // Start is called before the first frame update
    void Start()
    {
        //inputArea.text = "192.168.43.126";
    }

    // Update is called once per frame
    void Update()
    {

    }

    public void SetIPAdress()
    {
        UduinoWiFiSettings ipData = new UduinoWiFiSettings();
        ipData.ip = inputArea.text;
        ipData.port = 4222;
        ipData.enable = true;
        UduinoManager.Instance.UduinoWiFiBoards.Clear();
        UduinoManager.Instance.UduinoWiFiBoards.Add(ipData);
        UduinoManager.Instance.DiscoverPorts();
    }

    private IEnumerator checkifConnected()
    {
       
        yield return new WaitForSeconds(3f);
        UduinoManager.Instance.DiscoverPorts();
    }
}
