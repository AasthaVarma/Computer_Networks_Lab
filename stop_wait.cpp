#include<bits/stdc++.h>
using namespace std;

int main()
{
    srand(time(NULL));
    
    // number of frames to be sent
    int n = 10;
    int frames[n];
    // data in frames
    for(int i=0; i<n; i++)
        frames[i] = i;
    for(int i=0; i<n; i++)
        cout << frames[i] << " ";
    cout << "\n";
    
    //will_reach - whether or not packet will receive acknowledgement.
    // timeout is to resolve delayed acknowledgement
    // send_again handles lost data case
    int ack=1, will_reach, timeout=5, send_again;
    for(int i=0; i<n; i++)
    {
        cout << i << ": Sender: Frame to be sent:- " << frames[i] << "\n";
        send_again = rand()%timeout+2;
        if(send_again < timeout)
        {
            will_reach = rand()%2;
            if(will_reach == ack)
            {
                cout << "Receiver: Acknowledgement sent. \n\n";
                // reverse the acknowledgement i.e., if it's 1 then 0 vice-versa.
                ack = 1-ack;
            }
            else
            {
                cout << "Sender: Waiting for acknowledgment.\n";
                cout << "Sender: Sending previous frame again.\n";
                i--;
            }
        }
        else
        {
            cout << "Data is lost! So frame need to be sent again.\n";
            i--;
        }
    }
    return 0;
}
