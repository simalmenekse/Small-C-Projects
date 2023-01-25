#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAILS 1000
#define MAX_NAME 51
#define MAX_EMAIL_ID 1000
#define MAX_CONTENT 1000

typedef struct Vertex { //structers to create an adjacency graph
  char name[MAX_NAME]; //name variable
  int numEmailsSent; //variables to store numbers of emails and received emails
  int numEmailsReceived;
  int index; // New field to store index of vertex in graph
} Vertex;

typedef struct Edge { //structers to create an adjacency graph
  Vertex* from;
  Vertex* to;
  int weight;
} Edge;

typedef struct Graph { //structers to create an adjacency graph
  Vertex* vertices[MAX_EMAILS];
  Edge* edges[MAX_EMAILS][MAX_EMAILS];
  int numVertices;
  int numEdges;
} Graph;

Graph* createGraph() { //creating adjcency graph
  Graph* graph = (Graph*)malloc(sizeof(Graph));
  graph->numVertices = 0;
  graph->numEdges = 0;
  return graph;
}

Vertex* createVertex(Graph* graph, char* name) {
  // Check if vertex already exists
  for (int i = 0; i < graph->numVertices; i++) {
    if (strcmp(graph->vertices[i]->name, name) == 0) {
      return graph->vertices[i];
    }
  }

  // Create new vertex
  Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
  strcpy(vertex->name, name);
  vertex->numEmailsSent = 0;
  vertex->numEmailsReceived = 0;
  vertex->index = graph->numVertices; // Set index of vertex
  graph->vertices[graph->numVertices++] = vertex;
  return vertex;
}

void createEdge(Graph* graph, char* from, char* to, int weight) {
  Vertex* fromVertex = createVertex(graph, from);
  Vertex* toVertex = createVertex(graph, to);

  // Check if edge already exists
  for (int i = 0; i < graph->numEdges; i++) {
    if (graph->edges[i][0]->from == fromVertex && graph->edges[i][0]->to == toVertex) {
      graph->edges[i][0]->weight += weight;
      return;
    }
  }

  // Create new edge
  Edge* edge = (Edge*)malloc(sizeof(Edge));
  edge->from = fromVertex;
  edge->to = toVertex;
  edge->weight = weight;
  graph->edges[graph->numEdges][0] = edge;
  graph->numEdges++;
  fromVertex->numEmailsSent++;
  toVertex->numEmailsReceived++;
}

void printGraph(Graph* graph) {
  printf("The resulting graph's adjacency list:\n");
  for (int i = 0; i < graph->numVertices; i++) { // Printing the adjacency list
    Vertex* vertex = graph->vertices[i];
    printf("%s -> ", vertex->name);
    for (int j = 0; j < graph->numEdges; j++) {
      if (graph->edges[j][0]->from == vertex) {
        printf("%s | %d -> ", graph->edges[j][0]->to->name, graph->edges[j][0]->weight);
      }
    }
    printf("\n");
  }

  // Find people with maximum number of emails sent
  int maxEmailsSent = -1;
  for (int i = 0; i < graph->numVertices; i++) {
    if (graph->vertices[i]->numEmailsSent > maxEmailsSent) {
      maxEmailsSent = graph->vertices[i]->numEmailsSent;
    }
  }
  printf("People with the maximum number of emails sent:\n");
  for (int i = 0; i < graph->numVertices; i++) {
    if (graph->vertices[i]->numEmailsSent == maxEmailsSent) {
      printf("%s sent %d emails\n", graph->vertices[i]->name, graph->vertices[i]->numEmailsSent);
    }
  }

  // Find people with maximum number of words received
  int maxWordsReceived = -1;
  for (int i = 0; i < graph->numVertices; i++) {
    int wordsReceived = 0;
    for (int j = 0; j < graph->numEdges; j++) {
      if (graph->edges[j][0]->to == graph->vertices[i]) {
        wordsReceived += graph->edges[j][0]->weight;
      }
    }
    if (wordsReceived > maxWordsReceived) {
      maxWordsReceived = wordsReceived;
    }
  }
  printf("People with the maximum number of words received:\n");
  for (int i = 0; i < graph->numVertices; i++) {
    int wordsReceived = 0;
    for (int j = 0; j < graph->numEdges; j++) {
      if (graph->edges[j][0]->to == graph->vertices[i]) {
        wordsReceived += graph->edges[j][0]->weight;
      }
    }
    if (wordsReceived == maxWordsReceived) {
      printf("%s received %d words\n", graph->vertices[i]->name, wordsReceived);
    }
  }
}

int checkPathDFS(Graph* graph, Vertex* start, Vertex* end, int* visited) { // Function the check if there is a path between two names
  visited[start->index] = 1;
  if (start == end) {
    return 1;
  }
  for (int i = 0; i < graph->numEdges; i++) {
    if (graph->edges[i][0]->from == start && !visited[graph->edges[i][0]->to->index]) {
      if (checkPathDFS(graph, graph->edges[i][0]->to, end, visited)) {
        return 1;
      }
    }
  }
  return 0;
}

int checkPath(Graph* graph, char* from, char* to) { // Function the check if there is a path between two names
  Vertex* start = NULL;
  Vertex* end = NULL;
  for (int i = 0; i < graph->numVertices; i++) {
    if (strcmp(graph->vertices[i]->name, from) == 0) {
      start = graph->vertices[i];
    }
    if (strcmp(graph->vertices[i]->name, to) == 0) {
      end = graph->vertices[i];
    }
  }
  if (start == NULL || end == NULL) {
    return 0;
  }
  int visited[MAX_NAME] = {0};
  return checkPathDFS(graph, start, end, visited);
}

Graph* readEmails(char* path, int numFiles) { //Function to read the emails from the given directory
  Graph* graph = createGraph();
  for (int i = 1; i <= numFiles; i++) {
    char filePath[MAX_EMAIL_ID];
    sprintf(filePath, "%s/%d.txt", path, i);
    FILE* file = fopen(filePath, "r"); //Opening the necessary files with read mode
    if (file == NULL) {
      printf("Error: Could not open file %s\n", filePath);
      return graph;
    }
    int emailId;
    char sender[MAX_NAME];
    char recipient[MAX_NAME];
    int dayOfMonth;
    char content[MAX_CONTENT], ch;
    int words=0, characters=0;
    fscanf(file, "Email_ID: %d\nFrom: %s\nTo: %s\nDate: %d\n", &emailId, sender, recipient, &dayOfMonth); //reads the variables
    while ((ch = fgetc(file)) != EOF) // Reads the content untill the EOF and counts the words
    {
    	characters++;
    	if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0')
            words++;
    }
     if (characters > 0)
    {
        words++;
    }
    createEdge(graph, sender, recipient, words-1); //After reading the file, pass the variables to create the graph
    fclose(file); // Close the file
  }
  return graph;
}

int main() {
	
	 // Read the number of files from the user
	int num_files;
	printf("Enter the number of files: "); 
	scanf("%d", &num_files); // User inputs how many text files would be created in the given directory
	
	for (int i = 1; i <= num_files; i++) {
        // Open the file for writing
        char filename[256];
        sprintf(filename, "%d.txt", i);
        FILE *file = fopen(filename, "w"); // Open the files named as 1.txt, 2.txt till num_files.txt in write mode
        if (file == NULL) {
            perror("Error opening file");
            return 1;
        }

        // Read input from the user
        char sender[51], recipient[51], content[MAX_CONTENT];
		int date, eid;
		printf("Enter email ID: ");
		scanf("%d", &eid);
        printf("Enter the sender for file %d: ", i);
        scanf("%s", sender);
        printf("Enter the recipient for file %d: ", i);
        scanf("%s", recipient);
        printf("Enter the date for file %d: ", i);
        scanf(" %d", &date);
        getchar(); //Buffer solution
        printf("Enter the content for file %d: ", i);
        int c, contentIndex = 0;
  		while ((c = getchar()) != '\n' && c != EOF) { // Takes the input until "\n"
    			content[contentIndex++] = c;
  			}
  		content[contentIndex] = '\0';
        

        // Write the input to the file
        fprintf(file, "Email_ID: %d\nFrom: %s\nTo: %s\nDate: %d\nContent: %s",eid, sender, recipient, date, content);  // Creates the text files

        fclose(file);
    
	}
	
	char *dir_path ="/C Programming/data/email"; // Directory. Note that this should be changed according to your directory!!!
  	Graph* graph = readEmails(dir_path, num_files); // Passing the directory to the function as a string variable and number of files that is in the directory
  
 	 printGraph(graph);
  
 	char firstname[51], secondname[51]; // At the end, program asks user to enter 2 names. It checks if there is a path between these names and prints it to the screen.
  	printf("Enter the first name to check if there is a path between two names: ");
  	scanf("%s", firstname);
  	printf("Enter the second name: ");
  	scanf("%s", secondname);
 	int result = checkPath(graph, firstname, secondname);
  	printf("There is a path between %s and %s: %d\n",firstname, secondname, result);
  	
  	return 0;
}

 

