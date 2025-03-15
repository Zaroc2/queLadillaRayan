#include <iostream>
#include <fstream>

using namespace std;

template<typename T>
class Node{
	public:
	T payload;
	Node *next;
	Node *previous;
	Node(){
		next = previous = NULL;
	}
};

template<typename T>
class List{
	Node<T> *first,*last;
	public:
		List(){
			first = last = NULL;
		}
		Node<T>* getFirst(){
			return first;
		}
		Node<T>* getLast(){
			return last;
		}
		bool isEmpty(){
			if(first == NULL) return true;
			return false;
		}
        void add(T payload){
            addPost(last, payload);
        }
		void addPost(Node<T> *pos,T payload){	
			Node<T> *aux = new Node<T>;
			aux->payload = payload;
			
			if(first == NULL){//Si la lista est� vac�a, lo asignamos y ya
				first = last = aux;
				return;
			}
			
			Node<T> *aux2 = first;//En caso de que la lista no est� vac�a, creamos un puntero para buscar la posici�n P en donde quiere que lo insertemos
			
			while(aux2 != NULL){//Recorremos toda la lista hasta que lo encontremos
				if(aux2 == pos)
					break;
				aux2 = aux2->next;
			}
			
			
			if(aux2 == NULL){//Si el elemento no est� en la lista, lo a�adimos de ultimo
				aux->previous = last;
				last->next = aux;
				last = aux;
				aux->next = NULL;
				return;
			}
			//Si lo encontramos, entonces lo post-insertamos
			aux->next = aux2->next;
			aux->previous = aux2;
			aux2->next = aux;
			if(aux2 != last)
				aux->next->previous = aux;
			if(aux2 == last)
				last = aux;
			
			
		}
		void addPre(Node<T> *pos,T payload){
			Node<T> *aux = new Node<T>;
			aux->payload = payload;			
			if(first == NULL){//Si la lista est� vac�a, lo asignamos y ya
				first = last = aux;
				return;
			}
			
			Node<T> *aux2 = first;//En caso de que la lista no est� vac�a, creamos un puntero para buscar la posici�n P en donde quiere que lo insertemos
			
			while(aux2 != NULL){//Recorremos toda la lista hasta que lo encontremos
				if(aux2 == pos)
					break;
				aux2 = aux2->next;
			}
			if(aux2 == NULL){//Si el elemento no est� en la lista, lo a�adimos de �ltimo
				aux->previous = last;
				last->next = aux;
				last = aux;
				aux->next = NULL;
				return;
			}
			
			aux->previous = aux2->previous;
			aux->next = aux2;
			aux2->previous = aux;
			if(aux2 != first)
				aux->previous->next = aux;
			if(aux2 == first)
				first = aux;
			
		}
		void deleteItem(Node<T> *del){
			if(first == NULL)
				return;
			if(first == last){
				first = last = NULL;
				delete del;
				return;
			}
			if(del == first){
				first = del->next;
				first->previous = NULL;
				delete del;
				return;
			}
			if(del == last){				
				last = last->previous;
				last->next = NULL;
				delete del;
				return;
			}
			Node<T> *aux = first;
			while(aux != NULL){
				if(aux == del)
					break;
				aux = aux->next;
			}
			
			if(aux == NULL)
				return;
			
			aux->previous->next = aux->next;
			aux->next->previous = aux->previous;
			delete aux;
			
		}
		void deleteList(){
			while(first!=NULL){
				deleteItem(first);
			}
		}
		bool contains(T payload){
			Node<T>* aux = first;
			
			while(aux != NULL){
				if(aux->payload == payload)
					return true;
				aux = aux->next;
			}
			return false;
		}
		Node<T>* getItem(T payload){
			Node<T>* aux = first;
			while( aux != NULL){
				if(aux->payload == payload){
					return aux;
				}
				aux = aux->next;
			}
			return NULL;
		} 
	
};

template<typename T>
class PriorityList{
	List<T> lista;
	
	public:
		Node<T>* getFirst(){
			return lista.getFirst();
		}
		void add(Node<T> *payload){
			if(lista.isEmpty()){
				lista.addPre(NULL,payload->payload);//Si la lista est� vac�a, simplemente lo inserto y ya
				return;
			}
			
			Node<T>* aux = lista.getFirst();//Agarro el primero de la lista
			
			while(aux != NULL){
				if(aux->payload >= payload->payload){//Recorremos toda la lista hasta que hayamos encontrado uno mayor que el que queremos meter, y una vez encontrado
					break;
				}
				aux = aux->next;
			}
			lista.addPost(aux,payload->payload);//Una vez encontrado, lo insertamos antes
		}
		
		void deleteList(){
			lista.deleteList();
		}
		void pop(){
			lista.deleteItem(lista.getFirst());
		}
		bool isEmpty(){
			return lista.isEmpty();
		}
	
};

class Vertice;

class Edge{
    public:
    Vertice* end;
    float weight;
    Edge(){}
    Edge(Vertice* _end, float _weight){
        end = _end;
        weight = _weight;
    }
};

class Vertice{
    public:
    char name;
    float weightToReach;
    bool checked;
    Vertice* origin;
    List<Edge> adyacentVertices;

    Vertice() {}
    Vertice (char _name){
        name = _name;
        weightToReach = -1.0f;
        origin = nullptr;
        checked = false;
    }

    void saveAdyacent(Vertice* adyacent, float weight){
        Edge newAdyacent(adyacent, weight);

        adyacentVertices.add(newAdyacent);
    }
};

class Hechicero{
	public:
	string name;
	bool underInvestigation;
	List<int> spells; //los hechizos que hizo este :p

	Hechicero(){
	}
	Hechicero(string _name, bool _underInvestigation){
		name = _name;
		underInvestigation = _underInvestigation;
	}
};

class Hechizo{
	public:
	Vertice* graph;
	bool illegal;
	string wizardName;

	Hechizo(){}
	~Hechizo(){
		delete[] graph;
	}
};

Vertice* findBigger(Vertice* graph, int graphWeight){
    int max = -1;
    Vertice* smaller = nullptr;
    
    for (int i = 0; i < graphWeight - 1; i++ ){
        Vertice verticeAct = graph[i];
        if (!verticeAct.checked && verticeAct.weightToReach > max){
            smaller = &graph[i];
            max = verticeAct.weightToReach;
        }
    }

    return smaller;
}

float dijkstra(Vertice* graph, int graphWeight ){
    Vertice* u = &graph[0];
    float maxWeight = -1.0f;
    u->weightToReach = 0.0f;

    while(u != nullptr){
        for (Node<Edge>* i = u->adyacentVertices.getFirst(); i != nullptr; i = i->next){
            Vertice* adyacent = i->payload.end;

            if (!adyacent->checked && u->weightToReach + i->payload.weight > adyacent->weightToReach){
                adyacent->weightToReach = u->weightToReach + i->payload.weight;
                adyacent->origin = u;
            }
        }

        u->checked = true;

        u = findBigger(graph, graphWeight);
    }

    for (int i = 0; i < graphWeight; i ++){
        Vertice verticeAct = graph[i];
        if (verticeAct.weightToReach > maxWeight) maxWeight = verticeAct.weightToReach;
    }

    return maxWeight;
}

void readFile(Hechizo* &graphs, int* &graphSizes, List<Hechicero> &wizards, int &graphAmount){
	ifstream spellList("spellList.in");
	ifstream underInvestigation("underInvestigation.in");
	string inputString;
	int edgeAmount, vA, vB;
	float weight;
	bool found;

	if (!spellList.is_open() || !underInvestigation.is_open()) exit(1);

	spellList>>graphAmount;

	graphs = new Hechizo[graphAmount];
	graphSizes = new int[graphAmount];

	for (int i = 0; i < graphAmount; i++){
		getline(spellList, inputString);
		getline(spellList, inputString);

		wizards.add(Hechicero(inputString, false));
		wizards.getLast()->payload.spells.add(i);
		graphs[i].wizardName = inputString;

		spellList>>graphSizes[i];
		spellList>>inputString;

		graphs[i].graph = new Vertice[graphSizes[i]];

		for (int j = 0; j < graphSizes[i]; j++) graphs[i].graph[j] = Vertice(inputString[j]);

		spellList>>edgeAmount;
		
		for (int j = 0; j < edgeAmount; j++){
			spellList>>vA>>vB>>weight;

			--vA; --vB;

			graphs[i].graph[vA].saveAdyacent(&graphs[i].graph[vB], weight);
			graphs[i].graph[vB].saveAdyacent(&graphs[i].graph[vA], weight);	
		}
	}

	while (!underInvestigation.eof()){
		getline(underInvestigation, inputString);

		found = false;

		for (Node<Hechicero>* i = wizards.getFirst(); i != nullptr; i = i->next){
			if (i->payload.name == inputString){
				i->payload.underInvestigation = true;
				found = true;
				break;
			}
		}

		if (!found) wizards.add(Hechicero(inputString, true));
	}

	spellList.close();
	underInvestigation.close();
}

// ART. 1
bool hasOnlyOneConfluencePoint(Vertice* graph, int graphWeight){
	bool hasConfluence = false;
	for(int i = 0; i < graphWeight; i++){
		if(graph[i].name == 'A'){
			if(hasConfluence) return false;
			else hasConfluence = true;
		}
	}

	return hasConfluence;
}

// ART. 2
bool confuenceNextToEnergetic(Vertice* graph, int graphWeight) {
	for(int i = 0; i < graphWeight; i++){
		// encuentra el nodo 'A' - nodo de confluencia
		if(graph[i].name == 'A'){
			auto edges = graph[i].adyacentVertices;
			auto edge = edges.getFirst();
			// recorre todas las aristas
			while(edge != nullptr){
				// si no son energeticos - 'B' retorna falso
				if(edge->payload.end->name != 'B'){
					return false;
				}
			}
			return true;
		}
	}
	return true;
}

// ART. 3
bool hasLessThan3Runes(Vertice* graph, int graphWeight) {
	int rune[6] = {0,0,0,0,0,0};

	for(int i = 0; i < graphWeight; i++) {
		switch (graph[i].name) {
		case 'I':
			rune[0]=1;
			break;
		case 'Q':
			rune[1]=1;
			break;
		case 'T':
			rune[2]=1;
			break;
		case 'V':
			rune[3]=1;
			break;
		case 'L':
			rune[4]=1;
			break;
		case 'O':
			rune[5]=1;
			break;
		}
	}
	int numberOfRunes = 0;
	for(int i = 0; i < 6; i++){
		numberOfRunes += rune[i];
	}

	return numberOfRunes <= 3;
}

int main() {
	Hechizo* graphs;
	int* graphSizes;
	List<Hechicero> wizards;
	int graphAmount;

	readFile(graphs, graphSizes, wizards, graphAmount);

	for (Node<Hechicero>* i = wizards.getFirst(); i != nullptr; i = i->next){
		cout<<i->payload.name<<' '<<i->payload.underInvestigation<<endl;
		for (Node<int>* j = i->payload.spells.getFirst(); j != nullptr; j = j->next) cout<<j->payload<<' ';
		cout<<endl;
	}

	delete[] graphs;
	delete[] graphSizes;

    return 0;
}
