#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
//set a max number of numbers in the array
#define MAX 100000

void swap(int a[], int x, int y)
{
    int temp = a[x];
    a[x] = a[y];
    a[y] = temp;
}

int locOfSmallest(int a[], int s, int e)
{
    int i = s;
    int j = i;

    while (i <= e)
    {
        if (a[i] < a[j])
        {
            j = i;
        }

        i++;
    }

    return j;
}

void selSort(int a[], int n)
{
    int i = 0;
    while (i < n - 1)
    {
        int j = locOfSmallest(a, i, n - 1);
        swap(a, i, j);
        i++;
    }
}

void display(int a[], int n)
{
    int i = 0;
    while (i < n)
    {
        std::cout << a[i] << ", ";
        i++;
    }
}

int main()
{
    //user parameters
    float winX;
    float winY;
    int sleepTime = 0;
    int numOfnum = 10;

    //Get user inputs
    std::cout << "Window X: ";
    std::cin >> winX;
    std::cout << std::endl;
    std::cout << "Window Y: ";
    std::cin >> winY;
    std::cout << std::endl;
    std::cout << "SleepTime: ";
    std::cin >> sleepTime;
    std::cout << std::endl;
    std::cout << "NumberOfNumbers(the max is 100000): ";
    std::cin >> numOfnum;
    std::cout << std::endl;

    //bollean variables
    bool equal = false;
    bool completed = false;

    //integer variables
    int iSort = 0;
    int jSort = 0;
    int iMove;

    //set the values of the first array to the second array
    int arr[MAX];
    int sortedArr[MAX];
    for (int i = 0; i < numOfnum; i++)
    {
        arr[i] = rand() % 100000;
        sortedArr[i] = arr[i];
    }

    //sort the first array
    selSort(sortedArr, numOfnum);

    //find the last element in the array
    int e = sortedArr[numOfnum - 1];

    sf::RenderWindow window(sf::VideoMode(winX, winY), "Sorting Visualizer");
    while (window.isOpen())
    {
        //track the events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                std::cout << "THE SORTED ARRAY IS: " << std::endl;
                display(arr, numOfnum);
                std::cin.get();
            }
        }

        //calculate each rectangle width
        float rectWidth = winX / numOfnum;

        for (int i = 0; i < numOfnum; i++)
        {
            if (i == iSort)
            {
                equal = true;
            }

            //Calculate each rectangle height
            float rectHeight = (arr[i] * (winY - (winY / 10))) / e;

            //Creating a new rectangle with an outline
            sf::RectangleShape rect(sf::Vector2f(rectWidth, rectHeight));

            //Setting the position of the rectangle
            float yPos = winY - rectHeight;
            rect.setPosition(sf::Vector2f(i * rectWidth, yPos));

            //Making sure that the array was successfully sorted
            if (!completed)
            {
                //Adding visual effect to the sorting algorithm
                if (arr[numOfnum - 1] != sortedArr[numOfnum - 1])
                {
                    if (iSort != jSort)
                    {
                        if (equal)
                        {

                            if (i != jSort)
                            {
                                rect.setFillColor(sf::Color::Red);
                            }
                            else
                            {
                                equal = false;
                            }
                        }
                    }
                }
            }
            else
            {
                //change the color to green when everything is sorted
                rect.setFillColor(sf::Color::Green);
            }

            window.draw(rect);
        }

        if (iSort < numOfnum - 1)
        {
            jSort = locOfSmallest(arr, iSort, numOfnum - 1);
            swap(arr, iSort, jSort);
            iSort++;
        }
        else
        {
            completed = true;
        }

        //display and then clear the window
        window.display();
        window.clear();

        //Tak a pause to give time to the user to see the algorithm in action
        Sleep(sleepTime);
    }

    return 0;
}
