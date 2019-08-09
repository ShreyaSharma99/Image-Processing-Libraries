#include <bits/stdc++.h> 
#include <string> 
using namespace std;

int readFile(float **x, int n, string file)
{

//cout<<"1"<<endl;
	int count=0;
	float *a;
	a=(float*)malloc(sizeof(float)*(n*n));
	ifstream inFile;
	inFile.open(file.c_str());

//cout<<"1"<<endl;
	if (!inFile.is_open()) 
	{
		cout<<"file doesn't open"<<endl;
		return 0 ;
	}

	float word;
	//std::string::size_type sz; 
	while((inFile >> word) && count<(n*n))
	{
		a[count]=word;
		count++;
	}
	
	if(count<(n*n))
		{
			cout<<"Incompatible data"<<endl;
			return 0;
		}
		inFile.close();
	int t=0;
	for(int j=0; j<sqrt(count); j++)
	{
		for(int i=0; i<sqrt(count); i++)
		{
			x[i][j]=a[t];
			t++;
		}
	}
		return 1 ;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int readArray(float *v, int n, string file)
{
	int count=0;
	ifstream inFile;
	inFile.open(file.c_str());

//cout<<"1"<<endl;
	if (!inFile.is_open()) 
	{
		cout<<"file doesn't open"<<endl;
		return 0 ;
	}

	float word;

	while((inFile >> word) && count<n)
	{
		v[count]=word;
		count++;
	}
	if(count<(n))
		{
			cout<<"Incompatible data"<<endl;
			return 0;
		}
		inFile.close();

		return 1 ;

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// void convolution(float **a, int n, string s)
 float **convoWithoutPadding(float **Input, int sizeInput, float **Kernel, int sizeKernel){
    
    int sizeOut = sizeInput - sizeKernel + 1;
    float **matrixOut;
    matrixOut = (float**)malloc(sizeof(float*) * sizeOut);
    
    for(int i = 0; i < sizeOut; i++) {
        matrixOut[i] = (float*) malloc(sizeof(float*) * sizeOut);
    }
    
    float sum = 0.0;
    
    for(int i = 0; i < sizeOut; i++){
        for(int j = 0; j < sizeOut; j++){
             sum = 0.0;
            for(int u = 0; u < sizeKernel; u++){
                for(int v = 0; v < sizeKernel; v++){
                   
                    sum = sum + Input[u + i][v + j] * Kernel[sizeKernel - u -1][sizeKernel - v - 1];              
                }
            }
            
            matrixOut[i][j] = sum;
            
        }
    }
    
    return matrixOut;
    
}

 float **multWithoutPadding(float **Input, int sizeInput, float **Kernel, int sizeKernel){
    
    int sizeOut = sizeInput - sizeKernel + 1;
    
    int rows = sizeOut * sizeOut;
    int columns = sizeInput * sizeInput;
    
    float **newA;
    newA = (float**)malloc(sizeof(float*) * columns);
    
    for(int i = 0; i < rows; i++) {
        newA[i] = (float*) malloc(sizeof(float*) * columns);
    }
    
    float newB[columns][1];
    
    for(int i =0; i< columns; i++){
        
        newB[i][0] = 0.0;
    }
    
    // Invert the kernel as well here
    
    if(sizeKernel % 2 ==0){
    
      for(int i =0; i < sizeKernel/2; i++){
        
          for(int j = 0; j < sizeKernel ; j++){
            
            float temp;
            temp = Kernel[i][j];
            Kernel[i][j]= Kernel[sizeKernel - 1 - i][sizeKernel - 1 - j];
            Kernel[sizeKernel - 1 - i][sizeKernel - 1 - j] = temp;      
          }
      	}
    }
    
    else{

        for(int i =0; i < (sizeKernel -1)/2; i++){
        
          for(int j = 0; j < sizeKernel ; j++){
            
            float temp;
            temp = Kernel[i][j];
            Kernel[i][j]= Kernel[sizeKernel - 1 - i][sizeKernel - 1 - j];
            Kernel[sizeKernel - 1 - i][sizeKernel - 1 - j] = temp;
            
          }
        
        
        } 
        
        int p = (sizeKernel - 1)/2;
        
        for(int j=0; j< (sizeKernel -1)/2; j++){
           
            float temp;
            temp = Kernel[p][j];
            Kernel[p][j]= Kernel[sizeKernel - 1 - p][sizeKernel - 1 - j];
            Kernel[sizeKernel - 1 - p][sizeKernel - 1 - j] = temp; 
            
        } 
        
    }

    //kernel inverted
    
    int zeroCount = 0;
    int difference = sizeInput - sizeKernel;
    int countInA = 0;
    
    int currentRow = 0;
    
    int currentCol = 0;
    
    for(int i=0; i< rows; i++){
        
        currentRow = 0;
        currentCol = 0;
        
        countInA = 0;
        if((i%sizeOut==0)&& (i!=0)) zeroCount = zeroCount + sizeKernel -1 ;   //input - kernel + 1

        for(int j=0; j< columns ; j++){
            
            if(j < zeroCount)    newA[i][j]= 0.0; 
            else{
               
              if(countInA < sizeKernel *sizeKernel) {
               
                 if(currentCol == sizeKernel){
                    
                    currentRow ++;
                    currentCol = 0;
                    for(int z=0; z< difference; z++){
                        
                         newA[i][j+z] = 0.0;
                    }                   
                   
                    j = j + difference -1;
                }
               
                 else {
                     
                     newA[i][j] = Kernel[currentRow][currentCol];
                     currentCol ++;
                     countInA ++;
                 }
                 
              } 
              
              else{
                  newA[i][j] = 0.0;
              }
              
            }
            
        }
        
        zeroCount ++;
  //     cout << "\n";
    }

 
    
    int countTemp  = 0;
    
    for(int i =0; i< sizeInput; i++){
        
        for(int j =0; j < sizeInput ; j++){
            
            newB[countTemp][0] = Input[i][j];
                        
            countTemp++;
        }
        
    }
    cout << "\n";
    
    float **matrixOut;
    matrixOut = (float**)malloc(sizeof(float*) * sizeOut);
    
    for(int i = 0; i < sizeOut; i++) {
        matrixOut[i] = (float*) malloc(sizeof(float*) * sizeOut);
    }
    
    float newC[rows][1];
    
    float sum = 0.0;
    
    for(int i =0; i < rows; i++){
        
        sum = 0.0;    
        
        for(int j = 0 ; j< columns; j++)   {
           
            sum = sum + newA[i][j]* newB[j][0];
           
        }
        
        newC[i][0] = sum;    
        
    }
    
    int rowNo = 0;
    int colNo = 0;
    
    for(int i =0 ; i < rows; i++){
        
        if((i%sizeOut ==0) && (i!=0)){
            
            rowNo ++;
            colNo = 0;
            
        }
        
        matrixOut[rowNo][colNo] = newC[i][0];
        
        colNo ++;
        
        
    }
    
    
    for(int i = 0; i < rows; i++) {
        free(newA[i]);
    }
    free(newA);
     
    return matrixOut;
    
    
}


float **convoWithPadding(float **Input, int sizeInput, float **Kernel, int sizeKernel){
    
    // Assuming that the size of kernel is Odd. I guess that we should throw an error on 
    //the command prompt if we try to do this for an even sized kernel
    
    int padding = (sizeKernel -1 )/2;
    
    int newSize = sizeInput + 2*padding;
    
    float **newMatrixIn;
    newMatrixIn = (float**)malloc(sizeof(float*) * newSize);
    
    for(int i = 0; i < newSize; i++) {
        newMatrixIn[i] = (float*) malloc(sizeof(float*) * newSize);
    }
    
 
    for(int i = 0; i < newSize; i++){
        for(int j = 0; j < newSize; j++){
            
            if(i < padding) 
              newMatrixIn[i][j] = 0.0;
            
            else if(i >= newSize - padding)
              newMatrixIn[i][j] = 0.0;
              
            else if(j < padding)  
              newMatrixIn[i][j] = 0.0;
            
            else if(j>=newSize - padding)  
              newMatrixIn[i][j] = 0.0;  
             
            else 
              newMatrixIn[i][j] = Input[i- padding][ j- padding];  
        }
    }
    
    int sizeOut = sizeInput; 
    
    float **matrixOut;
    matrixOut = (float**)malloc(sizeof(float*) * sizeOut);
    
    for(int i = 0; i < sizeOut; i++) {
        matrixOut[i] = (float*) malloc(sizeof(float*) * sizeOut);
    }
    
    float sum = 0.0;
    
    for(int i = 0; i < sizeOut; i++){
        for(int j = 0; j < sizeOut; j++){
             sum = 0.0;
            for(int u = 0; u < sizeKernel; u++){
                for(int v = 0; v < sizeKernel; v++){
                   
                    sum = sum + newMatrixIn[u + i][v + j] * Kernel[sizeKernel - u -1][sizeKernel - v - 1];              
                }
            }
            
            matrixOut[i][j] = sum;
            
        }
    }
    
    return matrixOut;
    
}

float **multWithPadding(float **Input, int sizeInput, float **Kernel, int sizeKernel){
    
    // Assuming that the size of kernel is Odd. I guess that we should throw an error on 
    //the command prompt if we try to do this for an even sized kernel
    
    int padding = (sizeKernel -1 )/2;
    
    int newSize = sizeInput + 2*padding;
    
    float **newMatrixIn;
    newMatrixIn = (float**)malloc(sizeof(float*) * newSize);
    
    for(int i = 0; i < newSize; i++) {
        newMatrixIn[i] = (float*) malloc(sizeof(float*) * newSize);
    }
    
 
    for(int i = 0; i < newSize; i++){
        for(int j = 0; j < newSize; j++){
            
            if(i < padding) 
              newMatrixIn[i][j] = 0.0;
            
            else if(i >= newSize - padding)
              newMatrixIn[i][j] = 0.0;
              
            else if(j < padding)  
              newMatrixIn[i][j] = 0.0;
            
            else if(j>=newSize - padding)  
              newMatrixIn[i][j] = 0.0;  
             
            else 
              newMatrixIn[i][j] = Input[i- padding][ j- padding];  
        }
    }
    
    float **Answer;
    Answer = multWithoutPadding(newMatrixIn, newSize, Kernel, sizeKernel);
    
    return Answer;
    
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void non_linear_activation(float **a, int n, string str)
{

	float e=2.71828;

	float x,y;

	//applying relu
	if(str=="relu")
	{
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				if(a[i][j]<0)
					a[i][j]=0;
			}
		}
	}

	//applying tanh
	else{
			for(int i=0; i<n; i++)
			{
				for(int j=0; j<n; j++)
				{
					if(a[i][j]>65) a[i][j]=1;

					else
						{
							x=pow(e,a[i][j]);
							y=pow(e,-a[i][j]);

						a[i][j]=(x-y)/(x+y);
					}
				}
			}	
		}
//print final matrix
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			cout << a[i][j] << "  ";
		}

		cout << endl;
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//finding maximum
float max(float **x, int n)
{
	float m= x[0][0];
			
	for(int i=0; i<n/2; i++)
	{
		for(int j=0; j<n/2; j++)
		{
			if(m < x[i][j])
				m=x[i][j];
		}
	}
	return (float)m;
}

//finding average
float avg(float **x, int n)
{
	float a=0;

	for(int i=0; i<n/2; i++)
	{
		for(int j=0; j<n/2; j++)
		{
			a=a+x[i][j];
		}
	}

	//cout<< endl;

	return (float)(4*a/(n*n));
}


void pooling(float **a, int n, string s)
{	

		float **x;
		x = (float**)malloc(sizeof(float*)*n/2);

		for(int i=0; i<n/2; i++)
		{
			x[i]= (float*)malloc(sizeof(float)*n/2);
		}

		float y[2][2];
		float z[2][2];

		if(s=="maxPool")
		{	//max pooling
			for(int i=0; i<=n/2; i=i+n/2)
			{
				for(int j=0; j<=n/2; j=j+n/2)
				{
					for(int p=i; p<i+n/2; p++)
					{
						for(int q=j; q<j+n/2; q++)
						{
							x[p%(n/2)][q%(n/2)]=a[p][q];
						}
					}
					y[i/(n/2)][j/(n/2)] = max(x, n);
				}
			}

			//print max pooling
			cout << "The max pooling output is: "<< endl;
			cout << y[0][0] << "  " << y[0][1] << endl;
			cout << y[1][0] << "  " << y[1][1] << endl;
		}

		else
		{	//avg pooling
			for(int i=0; i<=n/2; i=i+n/2)
			{
				for(int j=0; j<=n/2; j=j+n/2)
				{
					for(int p=i; p<i+n/2; p++)
					{
						for(int q=j; q<j+n/2; q++)
						{
							x[p%(n/2)][q%(n/2)]=a[p][q];
						}
					}

					z[i/(n/2)][j/(n/2)] = avg(x, n);
				}
			}

			cout << "The avg pooling output is: "<< endl;
			cout << z[0][0] << "  " << z[0][1] << endl;
			cout << z[1][0] << "  " << z[1][1] << endl;
		}
		

	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	string str;
	cin >> str;
	string word[10];

	for(int i =0; i<6; i++)
	{
		word[i]="";
	}

	short counter = 0;

  
	for(short i=0;i<str.length();i++)
		{

		    if(str[i] == '-' ){
		   
		        counter++;
		        i++;
		    }
		    word[counter] += str[i];

		}

	for (int i = 0; i < argc; ++i) 
        {
        	 if((*argv[i]) == ' ' ){
		        counter++;
		        i++;
		    }
		     word[counter] += (*argv[i]);
        }
	
	string matrix1;
	string matrix2;
	string vector1;
	int d1;
	int d2;
	
	if(word[0]=="convoWithoutPadding")
	{
		matrix1 = word[1];
		matrix2 = word[3];
		//string vector;
		d1 = atoi(word[2].c_str());
		d2 = atoi(word[4].c_str());
		if(d1<=d2)
		{
			cout<<"invalid input: dim of kernel >= dim of input matrix"<<endl;
		}
		else{
				float **p;
				p = (float**)malloc(sizeof(float*)*d1);

				for(int i=0; i<d1; i++)
					p[i]= (float*)malloc(sizeof(float*)*d1);

				float **q;
				q = (float**)malloc(sizeof(float*)*d2);

				for(int i=0; i<d2; i++)
					q[i]= (float*)malloc(sizeof(float*)*d2);

				if(readFile(p,d1,matrix1)==1 && readFile(q,d2,matrix2)==1)   //for valid input from the txt file
				{
 			           
 			           	 float **Answer;					
				   	 Answer = convoWithoutPadding(p,d1,q,d2);
						
					// p = matrix1 is the INPUT matrix
					// q = matrix2 is the Kernel						
					// d1 = dimensions of p
					// d2 = dimensions of q
			
					int dimOut = d1 - d2 + 1;						

					for(int u = 0; u < dimOut; u++){
                   	                     for(int v = 0; v <dimOut; v++){
                   
                   				  cout << Answer[u][v] << " " ;        
    				             }
    
    
    					    cout << "\n";
    				       }
  
            
				    for(int i = 0; i < dimOut; i++) {
				         free(Answer[i]);
				     }
				     free(Answer);                                 	 
                                 
				}
			}
	}

	else if(word[0]=="convoWithPadding")
	{
				matrix1 = word[1];
		matrix2 = word[3];
		//string vector;
		d1 = atoi(word[2].c_str());
		d2 = atoi(word[4].c_str());

		
		if(d1<=d2)
		{
			cout<<"invalid input: dim of kernel >= dim of input matrix"<<endl;
		}
		
		else if(d2%2 == 0){
		    
			cout<<"invalid input: dim of kernel is even and hence padding not possible"<<endl;
		    
		    
		}
		
		else{
				float **p;
				p = (float**)malloc(sizeof(float*)*d1);

				for(int i=0; i<d1; i++)
					p[i]= (float*)malloc(sizeof(float*)*d1);

				float **q;
				q = (float**)malloc(sizeof(float*)*d2);

				for(int i=0; i<d2; i++)
					q[i]= (float*)malloc(sizeof(float*)*d2);

				if(readFile(p,d1,matrix1)==1 && readFile(q,d2,matrix2)==1)   //for valid input from the txt file
				{

 			           	 float **Answer;					
				   	 Answer = convoWithPadding(p,d1,q,d2);
						
					// p = matrix1 is the INPUT matrix
					// q = matrix2 is the Kernel						
					// d1 = dimensions of p
					// d2 = dimensions of q
			
					int dimOut = d1;						

					for(int u = 0; u < dimOut; u++){
                   	                     for(int v = 0; v <dimOut; v++){
                   
                   				  cout << Answer[u][v] << " " ;        
    				             }
    
    
    					    cout << "\n";
    				       }
  
            
				    for(int i = 0; i < dimOut; i++) {
				         free(Answer[i]);
				     }
				     free(Answer);                                 	 
                                 
				}
			}

	

	
	}

	else if(word[0]=="multWithoutPadding")
	{
		matrix1 = word[1];
		matrix2 = word[3];
		//string vector;
		d1 = atoi(word[2].c_str());
		d2 = atoi(word[4].c_str());
		if(d1<=d2)
		{
			cout<<"invalid input: dim of kernel >= dim of input matrix"<<endl;
		}
		else{
				float **p;
				p = (float**)malloc(sizeof(float*)*d1);

				for(int i=0; i<d1; i++)
					p[i]= (float*)malloc(sizeof(float*)*d1);

				float **q;
				q = (float**)malloc(sizeof(float*)*d2);

				for(int i=0; i<d2; i++)
					q[i]= (float*)malloc(sizeof(float*)*d2);

				if(readFile(p,d1,matrix1)==1 && readFile(q,d2,matrix2)==1)   //for valid input from the txt file
				{
 			           	 float **Answer;					
				   	 Answer = multWithoutPadding(p,d1,q,d2);
						
					// p = matrix1 is the INPUT matrix
					// q = matrix2 is the Kernel						
					// d1 = dimensions of p
					// d2 = dimensions of q
			
					int dimOut = d1 - d2 + 1;						

					for(int u = 0; u < dimOut; u++){
                   	                     for(int v = 0; v <dimOut; v++){
                   
                   				  cout << Answer[u][v] << " " ;        
    				             }
    
    
    					    cout << "\n";
    				       }
  
            
				    for(int i = 0; i < dimOut; i++) {
				         free(Answer[i]);
				     }
				     free(Answer);                                 	 
                                 
				}
			}
	}

	else if(word[0]=="multWithPadding")
	{
				matrix1 = word[1];
		matrix2 = word[3];
		//string vector;
		d1 = atoi(word[2].c_str());
		d2 = atoi(word[4].c_str());
		if(d1<=d2)
		{
			cout<<"invalid input: dim of kernel >= dim of input matrix"<<endl;
		}
		
		else if(d2%2 == 0){
		    
			cout<<"invalid input: dim of kernel is even and hence padding not possible"<<endl;
		    
		    
		}
		
		else{
				float **p;
				p = (float**)malloc(sizeof(float*)*d1);

				for(int i=0; i<d1; i++)
					p[i]= (float*)malloc(sizeof(float*)*d1);

				float **q;
				q = (float**)malloc(sizeof(float*)*d2);

				for(int i=0; i<d2; i++)
					q[i]= (float*)malloc(sizeof(float*)*d2);

				if(readFile(p,d1,matrix1)==1 && readFile(q,d2,matrix2)==1)   //for valid input from the txt file
				{
 			           	 float **Answer;					
				   	 Answer = multWithPadding(p,d1,q,d2);
						
					// p = matrix1 is the INPUT matrix
					// q = matrix2 is the Kernel						
					// d1 = dimensions of p
					// d2 = dimensions of q
			
					int dimOut = d1;						

					for(int u = 0; u < dimOut; u++){
                   	                     for(int v = 0; v <dimOut; v++){
                   
                   				  cout << Answer[u][v] << " " ;        
    				             }
    
    
    					    cout << "\n";
    				       }
  
            
				    for(int i = 0; i < dimOut; i++) {
				         free(Answer[i]);
				     }
				     free(Answer);                                 	 
                                 
				}
			}

	

	
	}
   

	else if(word[0]=="maxPool")
	{
		matrix1 = word[1];
		
		d1 = atoi(word[2].c_str());

		if(d1%2==1) 
		{
			cout<<"input matrix should have even dimensions"<<endl;
		}
	else
		{
			float **a;
			a = (float**)malloc(sizeof(float*)*d1);

			for(int i=0; i<d1; i++)
				a[i]= (float*)malloc(sizeof(float)*d1);

		int b = readFile(a, d1, matrix1);
			if(b==1)
				{
					pooling(a, d1, word[0]);
				}
		}
	}


	else if(word[0]=="avgPool")
	{
		matrix1 = word[1];
		d1 = atoi(word[2].c_str());

		if(d1%2==1) 
		{
			cout<<"input matrix should have even dimensions"<<endl;
		}

		else
		{	float **a;
			a = (float**)malloc(sizeof(float*)*d1);

			for(int i=0; i<d1; i++)
				a[i]= (float*)malloc(sizeof(float)*d1);

			int b = readFile(a, d1, matrix1);
			if(b==1)
				{
					pooling(a, d1, word[0]);
				}
		}
	}

	else if(word[0]=="relu")
	{
		matrix1 = word[1];
		d1 = atoi(word[2].c_str());

		float **a;
		a = (float**)malloc(sizeof(float*)*d1);

		for(int i=0; i<d1; i++)
			a[i]= (float*)malloc(sizeof(float)*d1);

		int b = readFile(a, d1, matrix1);
		if(b==1)
			{
				non_linear_activation(a, d1, word[0]);
			}

	}

	else if(word[0]=="tanh")
	{
		matrix1 = word[1];
		d1 = atoi(word[2].c_str());

		float **a;
		a = (float**)malloc(sizeof(float*)*d1);

		for(int i=0; i<d1; i++)
			a[i]= (float*)malloc(sizeof(float)*d1);
			
		int b = readFile(a, d1, matrix1);
		if(b==1)
			{
				non_linear_activation(a, d1, word[0]);
			}

	}


	else if(word[0]=="sigmoid")
	{
	    	matrix1 = word[1];
	        
        // please change the final ReadMe with you where you have to give the size of the matrix as well in the input

      			d1 = atoi(word[2].c_str());
	
		  float* v;
		  v = (float*)malloc(sizeof(float)*d1);

        // Just as you have a file read function for n * n matrix; make one for n * 1 matrix and name it readArray(float **v, int size, string fileName)

        if(readArray(v, d1, matrix1)==1)
            {
            	float ReturnVal[d1]; 
	    
	   			for (int i=0; i< d1 ; i++) 
	       		ReturnVal[i] = 1/(1 + exp(v[i])); 
	    
 				for (int i=0; i<d1; i++) 
	      		cout <<ReturnVal[i] << " ";
            //softmax_sigmoid(v, d1, "sigmoid");
            }
            
	}

	else if(word[0]=="softmax")
	{

	    	matrix1 = word[1];
	        
      			d1 = atoi(word[2].c_str());
	
		  float* v;
		  v = (float*)malloc(sizeof(float)*d1);

    if(readArray(v, d1, matrix1)==1)
        {
        	 float sum=0.0;

	    float ReturnVal[d1]; 

	    for (int i=0; i<d1; i++) 
	        sum = sum + exp(v[i]);
	    
	    for (int i=0; i<d1; i++) 
	        ReturnVal[i] = exp(v[i])/sum;
	 
	   for (int i=0; i<d1; i++) 
	      cout <<ReturnVal[i] << " ";
        }   

	}

	else {
		cout<<"Invalid command"<<endl;
	}

}
