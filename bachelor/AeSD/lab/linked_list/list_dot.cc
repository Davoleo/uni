#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;

// compilazione: g++ -xc++ lezione7-2-list-dot.c 
//
// Obiettivo:
// 1) analisi con grafo (insert front, front + tail)
// ./a.out -graph

// 2) analisi con grafo (insert after elem)
// ./a.out -graph

// 3) analisi con grafo (delete front, delete tail, delete node)
// ./a.out -graph

int ct_swap=0;
int ct_cmp=0;
int ct_op=0;  /// operazioni per la ricerca

int max_dim=0;
int ntests=1;
int ndiv=1;
int details=0;
int graph=0;


int n=0; /// dimensione dell'array

/// file di output per grafo
ofstream output_graph;
int n_operazione=0; /// contatore di operazioni per visualizzare i vari step






//////////////////////////////////////////////////
/// Definizione della struttura dati lista
//////////////////////////////////////////////////

/// struct per il nodo della lista
typedef struct node {
    int val;
    struct node * next;
} node_t;


/// struct per la lista
typedef struct list {
     node *head;
  // node* tail; /// per lista doubly linked
} list_t;

//////////////////////////////////////////////////
/// Fine Definizione della struttura dati lista
//////////////////////////////////////////////////



/// Questo e' un modo per stampare l'indirizzo node relativamente ad un altro di riferimento.
/// Permette di ottenere offset di piccola dimensione per essere facilmente visualizzati
/// Nota: il metodo non e' robusto e potrebbe avere comportamenti indesiderati su architetture diverse
/// L'alternativa corretta' e' utilizzare %p di printf: es. printf("%p\n",(void*) node);
/// con lo svantaggio di avere interi a 64 bit poco leggibili

list_t* global_ptr_ref=NULL;  /// usato per memorizzare il puntatore alla prima lista allocata

int get_address( void* node){
  return (int)((long)node-(long)global_ptr_ref);
}

void node_print_graph(node_t *n){

  output_graph << "node_" << get_address(n) << "_" << n_operazione <<  endl;
  output_graph << "[label=<\n<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\" >\n<TR> <TD CELLPADDING=\"3\" BORDER=\"0\"  ALIGN=\"LEFT\" bgcolor=\"#f0f0f0\" PORT=\"id\">";
  output_graph << get_address(n) << "</TD> </TR><TR>\n<TD PORT=\"val\">";
  output_graph << n->val << "</TD>\n <TD PORT=\"next\" ";
  if (n->next==NULL)
    output_graph << "bgcolor=\"#808080\"> NULL";
  else
    output_graph << "> " << get_address(n->next);
  output_graph <<  "</TD>\n</TR></TABLE>>];\n";

  if (n->next!=NULL){ /// disegno arco
    output_graph << "node_" << get_address(n) << "_" << n_operazione << ":next:c -> ";
    output_graph << "node_" << get_address(n->next) << "_" << n_operazione <<":id ;\n";
  }
  
}

void mark_node_print_graph(node_t* elem){
  /// disegna un nodo speciale che punta al nodo indicato
  
  output_graph << "iterator_" << n_operazione <<  endl;
  output_graph << "[label=\"it\"];";

  output_graph << "iterator_" << n_operazione << " -> ";
  output_graph << "node_" << get_address(elem) << "_" << n_operazione <<":id ;\n";
  
}
void list_print_graph(list_t *n){

  ///// stampa struttura list_t
  
  output_graph << "list_" << get_address(n) << "_" << n_operazione <<  endl;
  output_graph << "[label=<\n<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\" >\n<TR> <TD CELLPADDING=\"3\" BORDER=\"0\"  ALIGN=\"LEFT\" bgcolor=\"#f0f0f0\" PORT=\"id\">";
  output_graph << "list" << "</TD> </TR><TR>\n<TD PORT=\"next\" ";
  if (n->head==NULL)
    output_graph << "bgcolor=\"#808080\"> head: NULL";
  else
    output_graph << "> head: " << get_address(n->head) ;
  output_graph <<  "</TD>\n</TR></TABLE>>];\n";

  if (n->head!=NULL){ /// disegno arco
    output_graph << "list_" << get_address(n) << "_" << n_operazione << ":next:e -> ";
    output_graph << "node_" << get_address(n->head) << "_" << n_operazione <<":id ;\n";
  }

  /// stampa gli eventuali nodi della lista

    node_t* current = n->head;
    while (current != NULL) {
      node_print_graph(current);
      current = current->next;
    }
}


void list_node_print_graph(list_t* l,node_t* elem){
  node_print_graph(elem);
  list_print_graph(l);
}


void list_print(list_t *l){
  printf("Stampa lista\n");
  
  if (l->head == NULL){
    printf("Lista vuota\n");
  }
  else{
    printf("Head in address %d\n",get_address(l->head));
    
    node_t* current = l->head;

    while (current != NULL) {
      if (!details)
      printf("%d, ", current->val);
      else{ /// stampa completa 
	if (current->next==NULL)
	printf("allocato in %d [Val: %d, Next: NULL]\n",
	       get_address(current),
	       current->val);
	  else
	printf("allocato in %d [Val: %d, Next: %d]\n",
	       get_address(current),
	       current->val,
	       get_address(current->next)
	       );
      }
      current = current->next;
    }
    printf("\n");
  }
  
}



void list_print_reversed(list_t *l);


void print_status(list_t* l, node_t* n, string c, node_t* mark=NULL){
  
  /// stampa lista sul grafo la lista l con eventuale nodo n aggiuntivo (durante le operazioni di modifica) e eventuale mark
      output_graph <<  "subgraph cluster_"<< n_operazione << " {"<<endl;    
      output_graph <<  "label=\" " << c << "\";"<<endl;
      if (mark!=NULL){ // devo marcare qualcosa
	  mark_node_print_graph(mark);
	  list_print_graph(l);
      }
      else{
      if (n==NULL){ /// di solito se chiedo solo la lista e' l'ultima operazione della sequenza -> coloro di verde lo sfondo
	output_graph <<  "style=filled;\ncolor=\"#e0ffe0\";\n";
	list_print_graph(l);
      }
      else
	list_node_print_graph(l,n);
      }
      output_graph <<  "}"<<endl;
      n_operazione++;
}



list_t * list_new(void){
  list_t* l=new list;
  if (details){
    printf("Lista creata\n");
  }
  
  l->head=NULL;   //// perche' non e' l.head ?
  if (details){
    printf("Imposto a NULL head\n");
  }

  return l;
}


void list_delete(list_t *l){
  //// implementare rimozione dal fondo della lista
  //// deallocazione struct list
}

void list_insert_front(list_t *l, int elem){
  /// inserisce un elemento all'inizio della lista
  node_t* new_node = new node_t;
  new_node->next=NULL;
  
  if (graph) print_status(l,new_node,"INS FRONT: nuovo nodo");
  
  new_node->val=elem;

  if (graph) print_status(l,new_node,"INS FRONT: assegno valore");
  
  new_node->next=l->head;

  if (graph) print_status(l,new_node,"INS FRONT: next agganciato a lista");

  l->head = new_node;

  if (graph) print_status(l,NULL,"INS FRONT: lista punta a nuovo nodo");

}

void list_insert_tail(list_t *l, int elem){
  /// inserisce un elemento alla fine della lista
  /// dato che non c'e' puntatore a last in list_t (possibile miglioramento)
  /// bisogna scorrere tutta la lista!

  node_t* new_node = new node_t;
  new_node->next=NULL;
  
  if (graph) print_status(l,new_node,"INS TAIL: nuovo nodo");
  
  new_node->val=elem;

  if (graph) print_status(l,new_node,"INS TAIL: assegno valore");

  node_t* last_node = l->head;

  if (last_node==NULL){ // aggancio direttamente al nodo creato
    l->head=new_node;
  }
  else{
    // cerca ultimo nodo
    while (last_node!=NULL && last_node->next!=NULL)
      last_node=last_node->next;
    
    last_node->next=new_node;
  }
    
  if (graph) print_status(l,NULL,"INS TAIL: aggancio ultimo nodo a nuovo nodo");
  
}

void list_insert_after(list_t *l, int elem, int search_elem){
  /// inserisco il nuovo nodo con contenuto elem
  /// dopo il primo nodo con contenuto search_elem


  node_t* found_node = l->head;
  if (found_node!=NULL){ /// comincio la ricerca
    // continua a cercare se il nodo non ha il valore richiesto e c'e' ancora un nodo next
    while (found_node->val!=search_elem && found_node->next!=NULL){
      
      if (graph) print_status(l,NULL,"cerco el: ",found_node);
      
      found_node=found_node->next;
    }

    if (graph) print_status(l,NULL,"trovato el: ",found_node);

    if (found_node->val==search_elem){ // se il nodo ha il valore richiesto -> inserisci nuovo nodo

      /// creo nodo
      node_t* new_node = new node_t;
      new_node->next=NULL;
      new_node->val=elem;
  
      if (graph) print_status(l,new_node,"INS AFTER: nuovo nodo");
  
      new_node->next=found_node->next;

      if (graph) print_status(l,new_node,"INS AFTER: aggancio (nuovo nodo)->next al resto della lista");

      found_node->next=new_node;

      if (graph) print_status(l,NULL,"INS AFTER: aggancio la parte precedente della lista al nuovo nodo");
          
    }
  }
    

}
  

void list_delete_front(list_t *l){
  /// elimina il primo elemento della lista
  node_t* node = l->head; // il nodo da eliminare

  if (node==NULL)  // lista vuota
    return;

  l->head=node->next;
    
  if (graph) print_status(l,node,"DEL FRONT: aggancio lista a nodo successivo");

  node->next=NULL;

  if (graph) print_status(l,node,"DEL FRONT: sgancio puntatore da nodo da cancellare");

  delete node;

  if (graph) print_status(l,NULL,"DEL FRONT: cancello nodo");

}



void list_delete_tail(list_t *l){
  /// elimina l'ultimo elemento della lista
  /// dato che non c'e' puntatore a last in list_t (possibile miglioramento)
  /// bisogna scorrere tutta la lista
  /// Siamo sicuri che mantenere un puntatore a last element della lista risolva il problema?


  node_t* but_last_node = l->head; /// cerco penultimo elemento

  if (but_last_node==NULL){  // lista vuota
    return;
  }

  if (but_last_node->next==NULL){ // lista con un elemento

    l->head=NULL;
    
    if (graph) print_status(l,but_last_node,"DEL TAIL: lista vuota (bisogna rimuovere il nodo)");

    delete but_last_node;

    if (graph) print_status(l,NULL,"DEL TAIL:rimosso nodo");

    return;
  }

  /// caso generale
  else{
    // cerca penultimo nodo
    while (but_last_node->next->next!=NULL){ /// se il next del next e' nullo mi fermo -> il next e' l'ultimo!
      if (graph) print_status(l,NULL,"cerco penultimo: ",but_last_node);

      but_last_node=but_last_node->next;      
    }
      if (graph) print_status(l,NULL,"trovato penultimo: ",but_last_node);

    node_t* node_del = but_last_node->next;  /// nodo da cancellare
    
    but_last_node->next=NULL; // sgancio ultimo nodo
    if (graph) print_status(l,node_del,"DEL TAIL: sgancio ultimo nodo");
    
    delete node_del;

    if (graph) print_status(l,NULL,"DEL TAIL: rimosso nodo");      
  }
}



void list_delete_node(list_t *l, int search_elem){
  /// elimina il primo nodo che contiene search_elem 
  node_t* current_node = l->head; /// cerco nodo precedente al nodo che contiene search_elem (devo cambiare il suo next!)

  // casi speciali
  if (current_node==NULL){  // lista vuota
    return;
  }

  if (current_node->val==search_elem){ // lista con primo elemento da cancellare
    list_delete_front(l);
    return;
  }

  /// caso generale
  else{

    // cerca penultimo nodo
    while (current_node->next->next!=NULL && current_node->next->val != search_elem){ /// se il next del next e' nullo mi fermo -> il next e' l'ultimo! oppure current->next->val == search elem (trovato!)
      if (graph) print_status(l,NULL,"cerco precedente: ",current_node);

      current_node=current_node->next;
    }
      if (graph) print_status(l,NULL,"trovato precedente: ",current_node);

    if (current_node->next->val == search_elem){ /// se il nodo next e' il nodo che cerco, lo cancello
            
      node_t* node_del = current_node->next;  /// nodo da cancellare
    
      current_node->next=node_del->next; // bypass del nodo
      
      if (graph) print_status(l,node_del,"DEL NODE: connetto next del precedente al next del nodo");

      node_del->next=NULL;
      
      if (graph) print_status(l,node_del,"DEL NODE: sgancio next del nodo");
    
      delete node_del;

      if (graph) print_status(l,NULL,"DEL NODE: rimosso nodo");
    }
  }
}


int parse_cmd(int argc, char **argv){
  /// controllo argomenti
  int ok_parse=0;
  for (int i=1;i<argc;i++){
    if (argv[i][1]=='v'){
      details=1;
      ok_parse=1;
    }
    if (argv[i][1]=='g'){
      graph=1;
      ok_parse=1;
    }
  }

  if (argc > 1 && !ok_parse) {
    printf("Usage: %s [Options]\n",argv[0]);
    printf("Options:\n");
    printf("  -verbose: Abilita stampe durante l'esecuzione dell'algoritmo\n");
    printf("  -graph: creazione file di dot con il grafo dell'esecuzione (forza d=1 t=1)\n");
    return 1;
  }

  return 0;
}

int main(int argc, char **argv) {
  int i,test;

  if (parse_cmd(argc,argv))
    return 1;

  if (graph){
    output_graph.open("graph.dot");
    /// preparo header
    output_graph << "digraph g"<<endl; 
    output_graph << "{ "<<endl;
    output_graph << "node [shape=none]"<<endl;
    output_graph << "rankdir=\"LR\""<<endl;;
    output_graph << "edge[tailclip=false,arrowtail=dot];"<<endl;    
  }
  
  list_t* list = list_new();
  global_ptr_ref=list;
  
  list_insert_front(list,3);
  list_insert_front(list,1);
  list_insert_front(list,2);
  list_insert_tail(list,5);

  // list_insert_after(list, 7, 1);
  
  //list_delete_front(list);
  //list_delete_node(list,3);
  //list_delete_tail(list);
  
  list_print(list);
    
  // init random
  srand((unsigned) time(NULL));
  

  if (graph){
    /// preparo footer e chiudo file
    output_graph << "}"<<endl; 
    output_graph.close();
    cout << " File graph.dot scritto" << endl<< "Creare il grafo con: dot graph.dot -Tpdf -o graph.pdf"<<endl;
  }

  return 0;
}
