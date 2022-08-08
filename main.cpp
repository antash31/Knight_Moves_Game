
// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif


using namespace std;
using namespace std::chrono;
const int INF = 1e9+10;

//
int visited[8][8];          //This Matrix stores whether the block is visited or not, assigns 0 or 1 value
int level[8][8];            //This Matrix stores the minimum paths from src to ith row-jth col in int format
string addressBoard[8][8] = {""};  //This Matrix stores the path from src to the ith row-jth col in String format
string board[8][8] = {" "}; //Initialise all blocks as empty

int getXcoordinate(string s,int i){
    //Returns the X coordinate by converting character to integer
    return s[i] - 'a';
}
int getYcoordinate(string s,int j){
    //Returns the Y coordinate by converting character to integer
    return s[j] - '1';
}
string getcoordinatesFinal(char path,bool getX){
  string newPath="";
  if(getX){
  switch(path){
    case '0':
      newPath = "a";
      break;
    case '1':
      newPath = "b";
      break;
    case '2':
      newPath = "c";
      break;
    case '3':
      newPath = "d";
      break;
    case '4':
      newPath = "e";
      break;
    case '5':
      newPath = "f";
      break;
    case '6':
      newPath = "g";
      break;
    case '7':
      newPath = "h";
      break;
    default:
      cout<<"Error in Coordinates X final Conversion"<<endl;
    }
  }else{
    switch(path){
    case '0':
      newPath = "1";
      break;
    case '1':
      newPath = "2";
      break;
    case '2':
      newPath = "3";
      break;
    case '3':
      newPath = "4";
      break;
    case '4':
      newPath = "5";
      break;
    case '5':
      newPath = "6";
      break;
    case '6':
      newPath = "7";
      break;
    case '7':
      newPath = "8";
      break;
    default:
      cout<<"Error in Coordinates Y final Conversion"<<endl;
    }
  }
  return newPath;
}

//Returns the bool value for if the move is possible on the board or is it out of board length
bool isValid(int x, int y){
  return x>=0 && y>=0 && x<8 && y<8;
}

//The Elements from this Vector generate moves when added to i, in the movement at line no -
vector<pair<int,int>> movements= {{-1,2},{1,2},
{2,1},{2,-1},
{1,-2},{-1,-2},
{-2,1},{-2,-1}
};

pair<string,int> solvePath(string knightPosition, string targetPosition){
    int sourceX = getXcoordinate(targetPosition,0);
    int sourceY = getYcoordinate(targetPosition,1);
    int destX = getXcoordinate(knightPosition,0);
    int destY = getYcoordinate(knightPosition,1);
    
    
    queue<pair<int,int>> q;
    q.push({sourceX,sourceY});
    visited[sourceX][sourceY] = 1;
    level[sourceX][sourceY] = 0;
    
      while(!q.empty()){
      pair<int,int> v = q.front();
      int x = v.first;
      int y = v.second;
      q.pop();

      for(auto movement : movements){
        int moveX = movement.first + x;
        int moveY = movement.second + y;

        
        //NEW for optimisation
        if(moveX==destX && moveY==destY){
          level[moveX][moveY] = level[x][y] + 1;
          visited[moveX][moveY] = 1;
        
          //Storing the address of previous blocks
          
          addressBoard[moveX][moveY].append(addressBoard[x][y]);
          
          break;
          
          }
        //NEW for optimisation

        
        if(!isValid(moveX,moveY)) continue;

        if(!visited[moveX][moveY]){
          q.push({moveX,moveY});
          level[moveX][moveY] = level[x][y] + 1; //keeps the record and updates the number of moves to reach target
          visited[moveX][moveY] = 1;
          addressBoard[moveX][moveY] +=addressBoard[x][y];
          }
      }
      if(level[destX][destY] != INF){
        break;
      }
    }
  return make_pair(addressBoard[destX][destY],level[destX][destY]);//Returns the path and steps
}

void reset(){
  for(int i=0;i<8;++i){
    for(int j=0;j<8;++j){
      level[i][j] = INF;
      visited[i][j] = 0;
      }
  }
}



void printBoard(string targetPosition,int steps){
  int destX = getXcoordinate(targetPosition,0);
  int destY = getYcoordinate(targetPosition,1);
  
  string path = addressBoard[destX][destY];
  
  string newPath="";
  for(int i = 0;i<path.length();i+=2){
    newPath += getcoordinatesFinal(path[i],true);
    newPath += getcoordinatesFinal(path[i+1],false);
  }
  cout<<"\nPATH: "<<newPath<<"\n"<<endl;
  
  int step=steps;
  for(int i = path.size()-1;i>=0;i-=2){
        //X-Coordinate, convert integer-String to integer
        int y = path[i-1] - '0';
        int x = path[i] - '0';
        board[x][y] = to_string(step);
        step--;
  }
  cout<<"  --- --- --- --- --- --- --- ---"<<endl;
  for(int row=7; row>=0; row--){
    cout<<row+1<<"|";
    for(int cell=0; cell<8; cell++){
      if(board[row][cell]==""){
          cout<<"  "<<board[row][cell]<<" |";
          }else{
          cout<<" "<<board[row][cell]<<" |";
          }
    }
    cout<<endl<<"  --- --- --- --- --- --- --- ---"<<endl;
  }
  cout<<"   A   B   C   D   E   F   G   H "<<endl;
}

void setBoard(){
  //i represents row and j represents coloumn
  for(int i = 7;i>=0;i--){
    for(int j=0;j<8;j++){
      string cellAddress = to_string(i)+to_string(j);
      addressBoard[i][j] = cellAddress;
    }
  }
}

bool isPossible(int xCoordinate,int yCoordinate,string path){
  int prevYmove = getYcoordinate(path,path.length()-1); //Gives the last move y axis information
  int prevXmove = getXcoordinate(path,path.length()-2); //Gives the last move x axis information
  
  if(xCoordinate>=0 && xCoordinate<8 && yCoordinate>=0 && yCoordinate<8){//Checks validity of X & Y coordinate
  if((prevXmove+2==xCoordinate) && (prevYmove+1==yCoordinate||prevYmove-1==yCoordinate) || ((prevXmove-1==xCoordinate) && (prevYmove+2==yCoordinate || prevYmove-2==yCoordinate)) || ((prevXmove+1==xCoordinate) && (prevYmove+2==yCoordinate ||prevYmove-2==yCoordinate)) ||((prevXmove-2==xCoordinate) && (prevYmove-1==yCoordinate || prevYmove+1==yCoordinate))){
          return true;
   }
  }
  return false;
  }
  

bool Gameover(string playerPath,string s1,string s2){

string path = solvePath(s1,s2).first;
string newPath = "";

for(int i = 0;i<path.length();i+=2){
    newPath += getcoordinatesFinal(path[i],true);
    newPath += getcoordinatesFinal(path[i+1],false);
  }
  
cout<<"\n"<<newPath<<endl;
if(playerPath==newPath){
    return true;
}
else if(playerPath[playerPath.length()-1] == s2[1] && playerPath[playerPath.length()-2] == s2[0]){
    return true;
}
else{
    return false;
  }
}

//This function prints the winner and other data like score, path and number of moves
void displayResult(string playerPath[],int winner,int no,string path,string s2)
{
    int score[2];


    if(playerPath[0][playerPath[0].length()-1] == playerPath[1][playerPath[1].length()-1])
    {//If both have same path
        cout<<"\n\n\tIT'S A TIE!!"<<endl;
    }
    else
    {
        cout<<"\n\n\tPLAYER "<<winner<<" WINS THE GAME WITH "<<(playerPath[winner].length()/2)-1<<" MOVES"<<endl;
    }
    cout<<"\nNAME     ||  SCORE ||  PATH"<<endl;
    
    for(int i = 0;i<no;i++)
    {
        if(playerPath[i].length()==path.length() && playerPath[i][playerPath[i].length()-1] == s2[1])
        {//If PLayer took more moves than CPU
            score[i] = 100;
        }
        else
        {//Player took equal move as CPU
            score[i] = 50;
        }
        cout<<"PLAYER "<<i<< " ||  "<<score[i]<< "   ||  " <<playerPath[i]<<endl;
    }
}

int setupGame(int no,string s1,string s2){
  string choiceBoard[2][8][8];
  string path = solvePath(s1,s2).first;
  //Goes through each player's turn
  bool answerFound = false;
  bool stopGame = false; //totally depends on answerFound value, exists so that we can stop the game at the right time
  int xCoordinate;
  int yCoordinate;
  for(int i=0;i<no;i++){//putting D at the place where you have to reach, destination
    int destY = getXcoordinate(s2,0);
    int destX = getYcoordinate(s2,1);
    choiceBoard[i][destX][destY] = "D";
  }

  int winner;
  
  int move = 1; //Represents which move it iss
  
  string playerPath[] = {""};

  for(int i=0;i<no;i++){
    playerPath[i] = (s1);//Stores the starting position of each player, in chess language
  }
  string tempPath;//takes temporary input
  while(!answerFound){
    for(int i=0;i<no;i++){
      cout<<"  --- --- --- --- --- --- --- --- ";
        cout<<endl;
        for(int row = 7;row>=0;row--){
          cout<<row+1<<"|";
          for(int cell=0;cell<8;cell++){
          if(choiceBoard[i][row][cell]==""){
          cout<<"  "<<choiceBoard[i][row][cell]<<" |";
          }else{
          cout<<" "<<choiceBoard[i][row][cell]<<" |";
          }
        }
        cout<<endl;
        cout<<"  --- --- --- --- --- --- --- --- ";
        cout<<endl;
      }
      cout<<"   A   B   C   D   E   F   G   H "<<endl<<endl;
      cout<<"Enter your move "<<move<<" Player "<<i<<endl;
      retry://If the move given by player is wrong they will retry to give their move
      
      
      cin>>tempPath;
     

      xCoordinate = getXcoordinate(tempPath,0);
      yCoordinate = getYcoordinate(tempPath,1);
      
      if(isPossible(xCoordinate,yCoordinate,playerPath[i])){
        playerPath[i].append(tempPath); //Adds the path given by user in the playerPath array

        //here yCoordinate represents Row & xCoordinate represents column
        choiceBoard[i][yCoordinate][xCoordinate] = to_string(move);// update the board with the user move

        cout<<"   _   _   _   _   _   _   _   _ ";
        cout<<endl;
        for(int row = 7;row>=0;row--){
          cout<<row+1<<"|";
          for(int cell=0;cell<8;cell++){
          if(choiceBoard[i][row][cell]==""){
          cout<<"  "<<choiceBoard[i][row][cell]<<" |";
          }else{
          cout<<" "<<choiceBoard[i][row][cell]<<" |";
          }
        }
        cout<<endl;
        cout<<"  --- --- --- --- --- --- --- --- ";
        cout<<endl;
      }
        
      cout<<"   A    B    C    D    E    F    G    H "<<endl;
        }
      else{
        cout<<"ILLEGAL MOVE PLAYER "<<i<<endl;
        goto retry;
      }

      answerFound = Gameover(playerPath[i],s1,s2);//Checks if answer is found using Gameover function
      
        if(answerFound){
          stopGame = true;
          winner = i;
        }
    }
    
    if(stopGame){
      break;
    }else{
      move++; //Give another turn
    }
  }
  displayResult(playerPath,winner,no,path,s2);
  return 1;
}

string printRandomString(int n){
    char alphabet[3] = { 'f', 'g','h'};
 
    string res = "";
    for (int i = 0; i < n; i++){
        res = res + alphabet[rand() % 3];
      }
    string num = to_string(1 + (rand() % ( 8 - 1 + 1 )));
    return res+num;
}

int main(){
/*cout<<"  __  __ _       _                             _  __      _       _     _     __  __                      "<<endl;
cout<<" |  \/  (_)     (_)                           | |/ /     (_)     | |   | |   |  \/  |                    "<<endl;
cout<<" | \  / |_ _ __  _ _ __ ___  _   _ _ __ ___   | ' / _ __  _  __ _| |__ | |_  | \  / | _____   _____  ___ "<<endl;
cout<<" | |\/| | | '_ \| | '_ ` _ \| | | | '_ ` _ \  |  < | '_ \| |/ _` | '_ \| __| | |\/| |/ _ \ \ / / _ \/ __|"<<endl;
cout<<" | |  | | | | | | | | | | | | |_| | | | | | | | . \| | | | | (_| | | | | |_  | |  | | (_) \ V /  __/\__ \"<<endl;
cout<<" |_|  |_|_|_| |_|_|_| |_| |_|\__,_|_| |_| |_| |_|\_\_| |_|_|\__, |_| |_|\__| |_|  |_|\___/ \_/ \___||___/"<<endl;
cout<<"                                                             __/ |                                       "<<endl;
cout<<"                                                            |___/             "<<endl;
    */
    cout<<"\t\t\t\t\t*************************************************************************"<<endl;
    cout<<"\t\t\t\t\t\t\t\t    Knight Moves"<<endl;
    cout<<"\t\t\t\t\t*************************************************************************"<<endl;
    cout<<"\t\t\t\t\t\t\t\tMembers"<<endl;
    cout<<"\t\t\t\t\t\tArbash Hussain   Vidit Negi   Niharika Singh  Atharva Kumar"<<endl;
    cout<<"\t\t\t\t\t\t9920103050       9920103059   9920103037      99201030\n\n"<<endl;
    cout<<"\t\t\t\t\t\t\t\tPress enter to start playing!"<<endl;
    //getchar();
    //system("cls");
    //no -> number of players, max 2 allowed!
    int mode;
    cout<<"1. Play"<<endl;
    cout<<"2. Tutorial"<<endl;
    cin>>mode;
    if(mode==1){
    play:
    int no;
    reset();
    setBoard(); //Set the address on board cells
    cout<<"Enter no of Players: "<<endl;
    cin>>no;
    string s1,s2;
    srand(time(NULL)); //makes use of the computer's internal clock to control the choice of the seed. Since time is continually changing, the seed is forever changing. Remember, if the seed number remains the same, the sequence of numbers will be repeated for each run of the program.
    s2 = printRandomString(1);
    s1 = "a1";
    cout<<"You Start from: "<<s1<<endl;
    cout<<"Reach "<<s2<<" in minimum moves & be quick!"<<endl;
    setupGame(no,s1,s2); //Start the Game and return the winner
    int minSteps = solvePath(s1,s2).second;
    cout<<"\n\n\tShortest Path to reach "<<s2<<" is given below."<<endl;
    printBoard(s1,minSteps);
    }
    else if(mode == 2){
       cout<<"You are given a knight that can have 8 possible moves. Each move is two squares in a cardinal direction, then one square in an orthogonal direction."<<endl;
cout<<"  --- --- --- --- --- --- --- --- "<<endl;
cout<<"8|   |   |   |   |   |   |   |   |"<<endl;
cout<<"  --- --- --- --- --- --- --- --- "<<endl;
cout<<"7|   |   |   |   |   |   |   |   |"<<endl;
cout<<"  --- --- --- --- --- --- --- --- "<<endl;
cout<<"6|   |   | 1 |   | 2 |   |   |   |"<<endl;
cout<<"  --- --- --- --- --- --- --- --- "<<endl;
cout<<"5|   | 8 |   |   |   | 3 |   |   |"<<endl;
cout<<"  --- --- --- --- --- --- --- --- "<<endl;
cout<<"4|   |   |   | K |   |   |   |   |"<<endl;
cout<<"  --- --- --- --- --- --- --- --- "<<endl;
cout<<"3|   | 7 |   |   |   | 4 |   |   |"<<endl;
cout<<"  --- --- --- --- --- --- --- --- "<<endl;
cout<<"2|   |   | 6 |   | 5 |   |   |   |"<<endl;
cout<<"  --- --- --- --- --- --- --- --- "<<endl;
cout<<"1|   |   |   |   |   |   |   |   |"<<endl;
cout<<"  --- --- --- --- --- --- --- --- "<<endl;
cout<<"  A   B   C   D   E   F   G   H "<<endl;
       cout<<"You are required to find the minimum path needed for knight to reach the destination."<<endl;
       cout<<endl<<"For Example: If Knight is present at A1: only possible moves it can take are B3 or C2"<<endl;
       cout<<endl<<"\t\tIf Knight is present at D4: then it can take 8 possible moves, B3,B5,C2,C6,E2,E6,F3,F5"<<endl<<endl;
       cout<<endl<<"You are required to give input in chess language only"<<endl;
       cout<<endl<<"For Eg: a1,b3 where A represents X-axis and 1 represents Y-axis"<<endl;

       cout<<endl<<"1. Play"<<endl;
       cin>>mode;
       if(mode==1){
         goto play;
       }
    }
}

