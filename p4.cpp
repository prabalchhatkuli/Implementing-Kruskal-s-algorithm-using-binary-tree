#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include<iostream>
  
using namespace std;
 
//Prabal Chhatkuli
//DATA Structures
//Prof. Sourav Dutta
//


//--------------------------------------------creating graph------------------------------------  
  
//each edge for a graph
struct Edge 
{ 
    int src;
    int dest;
    int weight; 
}; 
  
// this class represents a connected Graph
struct Graph 
{ 
                 int numVertex, numEdge; 
                 struct Edge* edge; 
}; 
  

struct Graph* createGraph(int numVertex, int numEdge) 
{ 
    struct Graph* graph = new Graph; 
    graph->numVertex = numVertex; 
    graph->numEdge = numEdge; 
  
    graph->edge = new Edge[numEdge]; 
    return graph; 
} 

 //--------this is the same min heap that we did in class-----
//-------------------------------------------------min Heap--------------------------

//node for the mintop tree
 struct node{
	int data;
	int src;
	int dest;
	node* left;
	node* right;
};


//BST MINTOP TREE
class BSTminTop{
	node *head;
	public:
	node *createnode(int src, int dest, int tdata);
	node *push(node *root,int src, int dest, int tdata);
	void swap(node *x, node *y);
	void display(node *root);
	void arrange(node *root);
	void minTop(node *root);
	node* pop(node *root);
	void gethead(node* root);	
};

node *BSTminTop:: createnode(int src, int dest, int tdata)
{
	node *newnode= new node;
	newnode->data= tdata;
	newnode->src= src;
	newnode->dest= dest;
	newnode->left= NULL;
	newnode->right= NULL;

	return newnode;
}

node *BSTminTop:: push(node *root,int src,int dest, int tdata)
{
	if(root == NULL)
	{
		root= createnode(src, dest, tdata);
	}
	
	else if(tdata <= root->data)
	{
		root->left= push(root->left,src, dest, tdata);
	}
	else
	{
		root->right= push(root->right,src, dest, tdata);
	}
	arrange(root);
	return root;
}
	
void BSTminTop:: arrange(node* root)
{
	if(root!= NULL)
	{
		arrange(root->left);
		arrange(root->right);
		minTop(root);
	}
    return;
}

void BSTminTop:: minTop(node* root)
{
	node *min= root;
	node *rootLeft= root->left;
	node *rootRight= root->right;
		
	if(root->left!=NULL && rootLeft->data < root->data)
	{
		min =rootLeft;
	}

	if(root->right != NULL && rootRight->data < root->data)
	{
		min= rootRight;
	}

	if(root != min)
	{
		swap(min,root);
		minTop(min);
	}

   return;
}

void BSTminTop:: swap(node *x, node *y)
{
	int temp=x->data;
	int temp2=x->src;
	int temp3=x->dest;
	x->data= y->data;
	x->src= y->src;
	x->dest=y->dest;
	y->data= temp;
	y->src=temp2;
	y->dest=temp3;


  return;
}

void BSTminTop:: gethead(node* root)
{
	head= root;
        return;
}


node* BSTminTop::pop(node *root)
  {
        node *tempPrev=root;
          node *temp=root;
           bool rightOrLeft=0;
            if(root==NULL)
             {
                    return NULL;
                  }
                   while(temp->right!=NULL || temp->left!=NULL)
                    {
                           if(temp->right==NULL)
                            {
                                   rightOrLeft=true;
                                    tempPrev=temp;
                                     temp=temp->left;
                                  }
                             
                                     else
                                      {
                                             rightOrLeft=false;
                                              tempPrev=temp;
                                               temp=temp->right;
                                            }
                                           }
                                            root->data=temp->data;
                                             if(root->right!=NULL || root->left!=NULL)
                                              {
                                                     if(rightOrLeft==true)
                                                      {
                                                             tempPrev->left=NULL;
                                                          }
                                                            else
                                                            {
                                                                    tempPrev->right=NULL;
                                                                  }
                                                                }
                                                                delete temp;
                                                                temp=NULL;
                                                                   arrange(root);
                                                                   return root;
                                                                 }
 
  
//-------------------------------------------Part used to find the Union-------------------------
struct NodeForsubset 
{ 
    int parent; 
    int rank; 
}; 
  
int find(struct NodeForsubset listSubset[], int i) 
{  
    if (listSubset[i].parent != i)
    {
        listSubset[i].parent = find(listSubset, listSubset[i].parent); 
    }

    return listSubset[i].parent; 
} 
  

void Union(struct NodeForsubset subsets[], int x, int y) 
{ 
    //finding the given values to prevent cycles in the creation of MST
    int findX = find(subsets, x);     int findY = find(subsets, y); 
  
    // Attach smaller rank tree under root of high: finding union of the rank part
     if (subsets[findX].rank < subsets[findY].rank)   {       subsets[findX].parent = findY;     }
    else if (subsets[findX].rank > subsets[findY].rank)  {            subsets[findY].parent = findX;     }
   
    // If ranks are same, then make one as root and increase the rank 
    else    { 
        subsets[findY].parent = findX; 
        subsets[findX].rank++; 
    } 
} 
//---------------------------------------------------------------------------------------------------------
int main() 
{ 
    cout<<"OK"<<endl;
    int countVertex = 9;  
    int countEdge  = 14;
    //create grpah
    struct Graph* graph = createGraph(countVertex, countEdge); 

    //define min heap
    node* root= NULL;

    BSTminTop minheap;
cout<<"check1"<<endl;


    //manual input of the vertices
    graph->edge[0].src = 8; 
    graph->edge[0].dest = 2; 
    graph->edge[0].weight = 2; 
    root=minheap.push(root, 8,2,2);
    

    graph->edge[1].src = 0; 
    graph->edge[1].dest = 1; 
    graph->edge[1].weight = 4; 
    root=minheap.push(root,0,1,4);


    graph->edge[2].src = 8; 
    graph->edge[2].dest = 6; 
    graph->edge[2].weight = 6; 
    root=minheap.push(root,8,6,6);
    
    graph->edge[3].src = 7; 
    graph->edge[3].dest = 8; 
    graph->edge[3].weight = 7; 
    root=minheap.push(root,7,8,7);
     
    graph->edge[4].src = 1; 
    graph->edge[4].dest = 2; 
    graph->edge[4].weight = 8; 
    root=minheap.push(root,1,2,8);

    graph->edge[5].src = 5; 
    graph->edge[5].dest = 4; 
    graph->edge[5].weight = 10; 
    root=minheap.push(root,5,4,10);

    graph->edge[6].src = 3; 
    graph->edge[6].dest = 5; 
    graph->edge[6].weight = 14; 
    root=minheap.push(root,3,5,14);

    graph->edge[7].src = 7; 
    graph->edge[7].dest = 6; 
    graph->edge[7].weight = 1; 
    root=minheap.push(root,7,6,1);

    graph->edge[8].src = 6; 
    graph->edge[8].dest = 5; 
    graph->edge[8].weight = 2; 
    root=minheap.push(root,6,5,2);

    graph->edge[9].src = 2; 
    graph->edge[9].dest = 5; 
    graph->edge[9].weight = 4; 
    root=minheap.push(root,2,5,4);

    graph->edge[10].src = 2; 
    graph->edge[10].dest = 3; 
    graph->edge[10].weight = 7; 
    root=minheap.push(root,2,3,7);

    graph->edge[11].src = 0; 
    graph->edge[11].dest = 7; 
    graph->edge[11].weight = 8; 
    root=minheap.push(root,0,7,8);

    graph->edge[12].src = 3; 
    graph->edge[12].dest = 4; 
    graph->edge[12].weight = 9; 
    root=minheap.push(root,3,4,9);

    graph->edge[13].src = 1; 
    graph->edge[13].dest = 7; 
    graph->edge[13].weight = 11; 
    root=minheap.push(root,1,7,11);
    

cout<<"INSerted into mean heap, created graph"<<endl;
    
//-----------------------------------------------------Kruskals slgorithm----------------------------------------
    //following the algorith discussed in our class
    //1) sort all the edges
    //2) picking the smallest edge. checking cycle formation
                    //    if cycle formed , discard
                    //    else include
    //repeat for V-1 edges



    int numberOfVertices = countVertex;
    //array to store the resuulting MSt
    struct Edge res_Arr[numberOfVertices];
    int loopCount = 0; 
    int i = 0; 

    // Allocatee memory for creating V ssubsets 
    struct NodeForsubset *listSubsets = new NodeForsubset[numberOfVertices];  
  
    //insert V elements in the Array
    ////we now have an array of subsets initialized to their index and 0
    for (int i = 0; i < numberOfVertices; ++i) 
    { 
        listSubsets[i].parent = i; 
        listSubsets[i].rank = 0; 
    } 
  

//-----------------------------------------------------Imp part: following the algorithm-------------------------------
    while (loopCount < numberOfVertices - 1) 
    { 
        //the tree is already sorted
        //copying the root: smallest node into an edge
        struct Edge next_edge;
        next_edge.src=root->src;     next_edge.dest=root->dest;        next_edge.weight=root->data;
       
        //pop root:removing the smallest root from the min heap
        root=minheap.pop(root);
        minheap.arrange(root); 

        //finding the data in the created subset
        int TempSRC = find(listSubsets, next_edge.src);         int TempDEST = find(listSubsets, next_edge.dest); 
  
        // If including they are not equal include the values of the root into the array and increse the counter 
        if (TempSRC != TempDEST) 
        { 
            res_Arr[loopCount++] = next_edge;
            //call union
            Union(listSubsets, TempSRC, TempDEST); 
        } 
       //if equal make no changes
       } 

//_____________________________________________________________________________________________
    cout<<"FROM the Kruskal's algorithm, we get the following:"<<endl;
    cout<<"src , dest,  weight"<<endl;



    //declaring variable to store the weight
    int sumofweight=0;
    for (int i = 0; i < loopCount; ++i) 
    {
       cout<<res_Arr[i].src<<" , "<<res_Arr[i].dest<<"with weight "<<res_Arr[i].weight<<endl;
       sumofweight+=res_Arr[i].weight;
    }
    
    cout<<"The sum of all the weights is "<<sumofweight<<endl<<endl<<endl;

//no need to call destructor beacause everything has been popped

    return 0; 
}
