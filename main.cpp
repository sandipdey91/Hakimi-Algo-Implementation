#include <iostream>
#include <fstream>
// #include <cstdlib>

using namespace std;

void mergeSort(int *sequence, int first, int last);                             //mergeSort was used to sort the sequence
void merge(int *sequence, int first, int mid, int last);                        //fucntion to merge two sorted arrays
void hakimiSequence(int *sequence, int arrSize);                                //hakimi's function to determine if a sequence is graphical
void destructor(int *sequence);                                                 //deallocate memory

int main(int argc, char const *argv[]){                                         //driving function
 ifstream dataFile(argv[1]);                                                    //reading sequence from text file
 if(dataFile.is_open()){                                                        //check if the file is opened correctly
    string dataInserted;                                                        //initializing variables and flags
    int arrSize = 0, sum = 0;
    bool flag = true;
    int *sequence = NULL;

    while (dataFile >> dataInserted){                                           //reading degree sequence from text file
      if(dataInserted == "<")
  		    sequence = new int [100];                                             //allocating memory to the array using pointer
	    else if(dataInserted == ">"){                                             //if we reach at the end of one degree sequence perform the hakimi operation
          cout << "\n< ";
          for (int i=0; i<arrSize; i++){
              cout << sequence[i] << " ";
              sum = sum + sequence[i];
              if(sequence[i] < 0)
                flag = false;
          }

          cout << " >" << endl;
          mergeSort(sequence,0,arrSize-1);

          if(flag == false)
              cout << "Negative sequence numbers are not allowed\n" << endl;
          else if((sum%2) != 0)
              cout << "Sum of the degrees should always be even\n" << endl;
          else if(sequence[0]>=arrSize)
              cout << "Degrees can't be equal to or greater than total vertices\n" << endl;
          else
              hakimiSequence(sequence, arrSize);

          destructor(sequence);
          arrSize = 0;
        }
	   else{
		    sequence[arrSize] = stoi(dataInserted);                                 //storing the degree sequence into the array
        arrSize ++;
  	 }
   }
 }
 else
  cout << "\nError opening File\n" << endl;
}

void hakimiSequence(int *sequence, int arrSize){
  bool flag = true;
  int newArrSize = arrSize;

  for(int i=1; i<=arrSize; i++){
    int k = sequence[0];
    for(int j=1;j<=k;j++){
      sequence[j] = sequence[j] - 1;
      if(sequence[j] < 0){
        flag = false;
        break;
      }
    }
    if(flag == false)
        break;
    else{
        newArrSize = newArrSize - 1;
        for(int j=0;j<=(newArrSize+1);j++)
          sequence[j] = sequence[j+1];

        mergeSort(sequence,0,newArrSize);

        cout << "< ";
        for (int l=0; l< newArrSize; l++)
            cout << sequence[l] << " ";
        cout << " >" << endl;
    }

    if(sequence[0]==0)
      break;
 }

if(flag == true)
    cout <<"The sequence is graphical\n" << endl;
else
    cout << "The sequence is not graphical\n" << endl;
}


void mergeSort(int *sequence, int first, int last){
  if(first < last){
    int mid = (first + last)/2;
    mergeSort(sequence,first,mid);
    mergeSort(sequence,mid+1,last);

    merge(sequence, first, mid, last);
  }
}


void merge(int *sequence, int first, int mid, int last){
  int n1 = mid - first + 1;
  int n2 =  last - mid;

  int L[n1], R[n2];

  for (int i = 0; i < n1; i++)
      L[i] = sequence[first + i];
  for (int j = 0; j < n2; j++)
      R[j] = sequence[mid + 1+ j];

  int i = 0, j = 0, k = first;

  while (i < n1 && j < n2){
      if (L[i] >= R[j]){
          sequence[k] = L[i];
          i++;
      }
      else{
          sequence[k] = R[j];
          j++;
      }
      k++;
  }
  while (i < n1){
      sequence[k] = L[i];
      i++;
      k++;
  }
  while (j < n2){
      sequence[k] = R[j];
      j++;
      k++;
  }
}


void destructor(int *sequence){
  delete [] sequence;
  sequence = NULL;
}
