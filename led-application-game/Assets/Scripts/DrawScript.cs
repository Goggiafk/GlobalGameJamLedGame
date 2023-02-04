using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;

public class DrawScript : MonoBehaviour
{
    public FlexibleColorPicker fcp;
    [SerializeField] private Vector2 matrix;
    [SerializeField] private Transform matrixArea;
    [SerializeField] private GameObject matrixButtonPrefab;
    [SerializeField] private float buttonSize;
    [SerializeField] private float spacing;
    [SerializeField] private Vector2 startPosition;
    public GameObject[,] matrixOfPixels;
    private Vector2 applePosition;
    private Vector2 headPosition;
    //public Vector2[] snakeBody;
    private Vector2 direction;


    void Start()
    {
        matrixOfPixels = new GameObject[(int)matrix.x, (int)matrix.y];
        var currentPosition = startPosition;
        int k = 0;
        for (int i = 0; i < matrix.x; i++)
        {
            currentPosition.y = startPosition.y;
            for (int j = 0; j < matrix.y; j++)
            {
                GameObject pixelx = Instantiate(matrixButtonPrefab, matrixArea);
                matrixOfPixels[i, j] = pixelx;
                matrixOfPixels[i, j].GetComponent<RectTransform>().localPosition = new Vector3(currentPosition.x, currentPosition.y, 0);
                matrixOfPixels[i, j].gameObject.GetComponent<PixelScript>().SetMatrixPosition(j, i);
                currentPosition.y += buttonSize + spacing;
            }
            currentPosition.x += buttonSize + spacing;
        }
    }

    public void CurrentClickedGameObject(GameObject other, int id)
    {
        switch (other.tag)
        {
            case "ColorButton":
                other.GetComponent<Image>().color = fcp.color;
                break;
        }
    }

    public void StartSnakeMode()
    {
        //snakeBody = new Vector2[4];
        //matrixOfPixels[4,13].GetComponent<PixelScript>().LightPixel(fcp.color);
        //matrixOfPixels[4,14].GetComponent<PixelScript>().LightPixel(fcp.color);
        matrixOfPixels[4, 15].GetComponent<PixelScript>().LightPixel(fcp.color);

        headPosition = new Vector2(4, 15);
        //snakeBody[0] = new Vector2(4, 14);
        //snakeBody[0] = new Vector2(4, 13);
        //snakeBody[0] = new Vector2(4, 12);
        //snakeBody[0] = new Vector2(4, 11);


        //SpawnApple();
        StartMoving();
    }

    public void ChangeDirectionX(int x)
    {
        direction.x = x;
    }

    public void ChangeDirectionY(int y)
    {
        direction.y = y;
        GameManager.Instance.ledController.MovePlayer(direction);
    }

    public void StartMoving()
    {
        matrixOfPixels[(int)headPosition.x, (int)headPosition.y].GetComponent<PixelScript>().LightPixel(Color.black);
        headPosition += direction;


        if ((int)headPosition.y + (int)direction.y > (int)matrix.y || (int)headPosition.y + (int)direction.y < 0)
        {
            StopAllCoroutines();
            GameManager.Instance.ledController.CleanMatrix();
            return;
        }


        Vector2 newBodyPart = new Vector2(0, 0);
        //if (headPosition == applePosition)
        //{
        //    SpawnApple();
        //    newBodyPart = snakeBody[snakeBody.Length-1];
        //}

        //Vector2[] temp = new Vector2[snakeBody.Length + 1];

        //if (newBodyPart.x == 0 && newBodyPart.y == 0)
        //{
        //    matrixOfPixels[(int)snakeBody[snakeBody.Length - 1].x, (int)snakeBody[snakeBody.Length - 1].y].GetComponent<PixelScript>().LightPixel(Color.black);
        //}

        Vector2[] tArray = new Vector2[1];

        //for (int i = 0; i < snakeBody.Length; i++)
        //{
        //    if (i < tArray.Length - 1)
        //        tArray[i + 1] = snakeBody[i];   
        //}

        

        tArray[0] = headPosition;

        //snakeBody = tArray;

        //if (newBodyPart.x != 0 && newBodyPart.y != 0) { 
        //    snakeBody.CopyTo(temp, 0);
        //    temp[temp.Length-1] = newBodyPart;
        //    snakeBody = temp;
        //}

        matrixOfPixels[(int)headPosition.x, (int)headPosition.y].GetComponent<PixelScript>().LightPixel(fcp.color);

        //for (int i = 1; i < snakeBody.Length; i++)
        //{
        //    matrixOfPixels[(int)snakeBody[i].x, (int)snakeBody[i].y].GetComponent<PixelScript>().LightPixel(fcp.color);
        //}

        //StartCoroutine(Timer(0.25f, () => {
        //    StartMoving();
        //}));
    }

    private void SpawnApple()
    {
        applePosition = new Vector2(Random.Range(1, (int)matrix.x - 1), Random.Range(1, (int)matrix.y - 1));
        matrixOfPixels[(int)applePosition.x, (int)applePosition.y].GetComponent<PixelScript>().LightPixel(Color.red);
    }

    public void UndoPixel()
    {
        Vibration.Vibrate(1000);
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
