using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Uduino;
using UnityEngine.UI;
using TMPro;

public class TextLedController : MonoBehaviour
{
    [SerializeField] private FlexibleColorPicker fcp;
    [SerializeField] private TMP_InputField inputArea;
    [SerializeField] private TMP_InputField scrollSpeedArea;
    [SerializeField] private TMP_InputField partyModeSpeedArea;

    [SerializeField] private TextMeshProUGUI pairedStatus;
    [SerializeField] private TextMeshProUGUI connectionStatus;

    [SerializeField] private Slider powerSlider;

    [SerializeField] private GameObject[] appWindows;
    [SerializeField] private GameObject[] appButtons;
    [SerializeField] private GameObject[] bluetoothElements;
   // [SerializeField] private GameObject battery;
    [SerializeField] private GameObject[] batteryLevels;

    private bool isMenuActive;
    private bool IsConnected;
    private bool isTimer;
    private bool hasSecondPassed;
    public static string dataRecived = "";
    // Start is called before the first frame update
    void Start()
    {
        SetAllElementsActive(false);
        isMenuActive = false;
        IsConnected = false;
        BluetoothService.CreateBluetoothObject();
    }

    void Update()
    {
        if (IsConnected)
        {
            try
            {
                string datain = BluetoothService.ReadFromBluetooth();
                if (datain.Length > 1)
                {
                    dataRecived = datain;
                    //print(dataRecived);
                    if (dataRecived == "medium" || dataRecived == "low" || dataRecived == "high") SetItemPanel(dataRecived);
                }

                if(isMenuActive == false)
                {
                    SetAllElementsActive(true);
                    isMenuActive = true;
                }
            }
            catch (Exception e)
            {
                IsConnected = false;
            }
        }
        else if(isMenuActive == true)
        {
            SetAllElementsActive(false);
            isMenuActive = false;
        }

        connectionStatus.text = "Connection Status: " + IsConnected;

        if (isTimer && hasSecondPassed && IsConnected)
        {
            hasSecondPassed = false;
            StartCoroutine(Timer(1,() => {
                BluetoothService.WritetoBluetooth("lnt`" + DateTime.Now.ToString() + "`");
                SetColorOfText();
                hasSecondPassed = true;
            }));
        }
    }

    public void SetAllElementsActive(bool state)
    {
        for (int i = 0; i < appWindows.Length - 1; i++)
        {
            if (!state)
                appWindows[i].SetActive(state);
            appButtons[i].SetActive(state);
        }
        appWindows[3].SetActive(true);
        //battery.SetActive(state);
        for (int i = 0; i < bluetoothElements.Length; i++)
        {
            bluetoothElements[i].SetActive(state);
        }
    }

    private void SetItemPanel(string level)
    {
        for (int i = 0; i < batteryLevels.Length; i++)
        {
            batteryLevels[i].SetActive(false);
        }
        switch (level)
        {
            case "low":
                batteryLevels[0].SetActive(true);
                break;
            case "medium":
                batteryLevels[1].SetActive(true);
                break;
            case "high":
                batteryLevels[2].SetActive(true);
                break;
        }
    }

    public void StartButton()
    {
        if (!IsConnected)
        {
            print("ESP32 Badge");
            IsConnected = BluetoothService.StartBluetoothConnection("ESP32 Badge");
        }
    }

    public void StopButton()
    {
        if (IsConnected)
        {
            IsConnected = false;
            BluetoothService.StopBluetoothConnection();
        }
    }

    public void SetColorOfText()
    {
        BluetoothService.WritetoBluetooth("stc`" + fcp.color.r * 255 + "`" + fcp.color.g * 255 + "`" + fcp.color.b * 255 + "`");
    }

    public void LoadData()
    {
        string rgbArray = "{";
        int arrayint = 0;

        foreach (var item in GameManager.Instance.drawScript.matrixOfPixels)
        {
            var pixelC = item.GetComponent<PixelScript>().rgb;
            rgbArray += "matrix.Color(" + pixelC.r * 255 + ", " + pixelC.g * 255 + ", " + pixelC.b * 255 + "), ";
            arrayint++;
            if(!(arrayint < 32))
            {
                arrayint = 0;
                rgbArray += "},\n{";
            }
        }

        Debug.Log(rgbArray);
        
    }

    public void NextReplica()
    {
        BluetoothService.WritetoBluetooth("cr`");
    }

    public void PickWeapon(int weapon)
    {
        BluetoothService.WritetoBluetooth("pw`" + weapon + "`");
    }

    public void AttackEnemy()
    {
        BluetoothService.WritetoBluetooth("ae`");
    }

    public void MovePlayer(Vector2 direction)
    {
        BluetoothService.WritetoBluetooth("mp`" + direction.x + "`" + direction.y + "`");
    }

    public void DisplayContext()
    {
        //var text = ChangeSpaces(inputArea.text.ToCharArray());
        if (IsConnected && (inputArea.text.ToString() != "" || inputArea.text.ToString() != null))
        {
            BluetoothService.WritetoBluetooth("lnt`" + inputArea.text.ToString() + "`");
        }
        //UduinoManager.Instance.sendCommand("sss", scrollSpeedArea.text);
        //UduinoManager.Instance.sendCommand("spms", partyModeSpeedArea.text);
        //UduinoManager.Instance.sendCommand("lnt", text);
    }
    public void DisplayContextStatic()
    {
        var text = ChangeSpaces(inputArea.text.ToCharArray());
        UduinoManager.Instance.sendCommand("spms", partyModeSpeedArea.text);
        UduinoManager.Instance.sendCommand("lnst", text);
    }

    public void StartTimer()
    {
        if (isTimer)
        {
            isTimer = false;
            hasSecondPassed = false;
        } else
        {
            isTimer = true;
            hasSecondPassed = false;
        }
    }

    private string ChangeSpaces(char[] text)
    {
        for (int i = 0; i < text.Length; i++)
        {
            if(text[i] == ' ')
            {
                text[i] = '`';
            }
        }
        string s = new string(text);
        return s;
    }
    
    public void ValueChangeCheck()
    {
        var ledPower = powerSlider.value;
        BluetoothService.WritetoBluetooth("cp`" + ledPower.ToString() + "`");
        //UduinoManager.Instance.sendCommand("cp", ledPower);
    }
    public void PaintPixel(int x, int y, Color rgb)
    {
        BluetoothService.WritetoBluetooth("pp`" + x.ToString() + "`" + y.ToString() + "`" + (rgb.r * 255).ToString() + "`" + (rgb.g * 255).ToString() + "`" + (rgb.b * 255).ToString() + "`");
        //UduinoManager.Instance.sendCommand("cp", ledPower);
    }

    public void CleanMatrix()
    {
        BluetoothService.WritetoBluetooth("cl`");
        var pixels = FindObjectsOfType<PixelScript>();

        foreach (var pixel in pixels)
        {
            pixel.GetComponent<Image>().color = Color.black;
        }
    }

    public void SendCommand(string command)
    {
        BluetoothService.WritetoBluetooth(command + "`");
    }

    public void ScrollText()
    {
        if (IsConnected && (inputArea.text.ToString() != "" || inputArea.text.ToString() != null))
        {
            BluetoothService.WritetoBluetooth("st`" + inputArea.text.ToString() + "`");
        }
        SetColorOfText();
        BluetoothService.WritetoBluetooth("sss`" + scrollSpeedArea.text + "`");
    }

    public void IsPartyMode(bool state)
    {
        char st = ' ';
        if (state) st = '1';
        else st = '0';
        UduinoManager.Instance.sendCommand("spms", partyModeSpeedArea.text);
        UduinoManager.Instance.sendCommand("spm", st);
    }

    public void IsAnimMode(bool state)
    {
        char st = ' ';
        if (state) st = '1';
        else st = '0';
        //var text1 = ChangeSpaces(animArea1.text.ToCharArray());
        //var text2 = ChangeSpaces(animArea2.text.ToCharArray());
        //var text3 = ChangeSpaces(animArea3.text.ToCharArray());
        //UduinoManager.Instance.sendCommand("lat1", text1);
        //UduinoManager.Instance.sendCommand("lat2", text2);
        //UduinoManager.Instance.sendCommand("lat3", text3);
        UduinoManager.Instance.sendCommand("spms", partyModeSpeedArea.text);
        UduinoManager.Instance.sendCommand("sam", st);
    }


    public void IsInverse(bool state)
    {
        //char st = ' ';
        //if (state) st = '1';
        //else st = '0';
        //UduinoManager.Instance.sendCommand("sim", st);
    }

    public void SetAligment(int id)
    {
        BluetoothService.WritetoBluetooth("sa`" + id + "`");
    }

    public void SetScrollAligment(int id)
    {
        //UduinoManager.Instance.sendCommand("ssa", id);
        //var text = ChangeSpaces(inputArea.text.ToCharArray());
        //UduinoManager.Instance.sendCommand("lnt", text);
    }

    private IEnumerator Timer(float time, System.Action action)
    {
        while (time > 0)
        {
            time -= Time.deltaTime;
            yield return null;
        }

        action();
    }
}
