#include <stack>
#include "Data.h"

bool Data::readStations(string filename) {
    ifstream input(filename);
    string labels = "Name,District,Municipality,Township,Line";
    if (input.is_open()){
        string l;
        getline(input, l);
        if(l == labels) {
            int id = 1;
            string name, district, municipality, township, line;
            string field;
            vector<string> fields;
            char quote_char = '"';
            while (getline(input, l)) {
                stringstream iss(l);
                while (getline(iss, field, ',')){
                    fields.push_back(field);
                    if (field[0] == quote_char && field.back() != quote_char){
                        getline(iss, field, '"');
                        fields.back() += "," + field + '"';         //add a comma, because it is part of the input and was lost because of the getline
                        getline(iss, field, ',');       //consume the comma
                    }
                }

                name = fields[0];
                district = fields[1];
                municipality = fields[2];
                township = fields[3];
                line = fields[4];

                districts.insert(district);
                municipalities.insert(municipality);

                if(names.insert({name,id}).second){      //(names.insert(name).second) return false if element already exists
                    Station* station = new Station(name,district,municipality,township,line);
                    Vertex* v = new Vertex(id);
                    v->setStation(station);
                    g.addVertex(v);
                    id++;
                }
                fields.clear();
            }
            stations = filename;
            return true;
        } else cout << "\nFile content for " << filename << " is incorrect. Please submit the right file.\n";
    } else cout << "\nCould not open " << filename << endl;
    return false;
}

bool Data::readNetwork(std::string filename) {
    ifstream input(filename);
    string labels = "Station_A,Station_B,Capacity,Service";
    if (input.is_open()){
        string l;
        getline(input, l);
        if(l == labels) {
            string station_A, station_B, capacity, service;
            int counter = 1;
            string field;
            vector<string> fields;
            char quote_char = '"';

            while (getline(input, l)) {
                stringstream iss(l);
                Vertex* vA = nullptr; Vertex* vB = nullptr;

                while (getline(iss, field, ',')){
                    fields.push_back(field);
                    if (field[0] == quote_char && field.back() != quote_char){
                        getline(iss, field, '"');
                        fields.back() += "," + field + '"';         //add a comma, because it is part of the input and was lost because of the getline
                        getline(iss, field, ',');       //consume the comma
                    }
                }
                station_A = fields[0];
                station_B = fields[1];
                capacity = fields[2];
                service = fields[3];
                counter++;
                for (auto v : g.getVertexSet()){ // find vertex
                    Station* s = v->getStation();
                    if(s->getName() == station_A) vA = v;
                    else if(s->getName() == station_B) vB = v;
                    if(vA != nullptr && vB != nullptr) break; // both vertex were found.
                }
                fields.clear();

                if(!g.addBidirectionalEdge(vA, vB, stod(capacity), service)){
                    cout << "\nOn line " << (counter) <<", there are stations that do not exist.\n";
                    //return false;
                }
            }
            network = filename;
            return true;
        } else cout << "\nFile content for " << filename << " is incorrect. Please submit the right file.\n";
    } else cout << "\nCould not open " << filename << endl;
    return false;
}

Graph Data::getG() const {
    return g;
}

void Data::setG(Graph g) {
    this->g = g;
}

map<string, int> Data::getNames() const {
    return names;
}

/**
 * Retorna o flow máximo (ou seja, número máximo de comboios) que podem atravessar o percurso de 'source' até 'target' (argumentos fornecidos).
 * @param source id do vértice de partida (relacionado com uma dada estação)
 * @param target id do vértice de destino (relacionado com uma dada estação)
 * @return valor double correspondente ao numero maximo de comboios que podem atravessar o dado percurso
 */
double Data::getMaxFlow(queue<int> source, int target) {
    for (Vertex* v : g.getVertexSet()){
        for (Edge* e : v->getAdj()){
            e->setFlow(0);
        }
        /*for (Edge* e : v->getIncoming()) {
            e->setFlow(0);

            Edge* reverse = new Edge(e->getDest(), e->getOrig(), e->getWeight());
            reverse->setFlow(0);
            reverse->setReverse(e);
            e->setReverse(reverse);
        }*/
    }

    double bottleneck;
    while (path(source, target)){
        bottleneck = findBottleneck(target);
        augmentPath(target, bottleneck);
    }

    double maxFlow = 0;
    Vertex* sink = g.findVertex(target);
    for (Edge* e : sink->getIncoming())
        maxFlow += e->getFlow();
    return maxFlow;
}

/**
 * Retorna verdadeiro ou falso, consoante a existencia de um percurso até ao vertex de id 'target' (estação de destino) a partir das estações de partida. Caso exista, define esse caminho através do parâmetro 'path' dos vértices do grafo.
 * @param s queue de valores inteiros que correspondem aos ids das estações de partida
 * @param target id do vértice de destino (relacionado com uma dada estação)
 * @return valor booleano correspondente à existencia de um percurso até ao vertex de id 'target' (estação de destino)
 */
bool Data::path(queue<int> s, int target) {
    for (Vertex* v : g.getVertexSet()){
        v->setVisited(false);
        v->setPath(nullptr);
    }

    while (!s.empty()){
        Vertex* v = g.findVertex(s.front());
        if (v->getId() == target){
            s.pop();
            continue;
        }
        v->setVisited(true);
        for (Edge* e : v->getAdj()) {
            if (!e->getDest()->isVisited() && e->getWeight() - e->getFlow() > 0) {
                s.push(e->getDest()->getId());
                e->getDest()->setVisited(true);
                e->getDest()->setPath(e);
                if (e->getDest()->getId() == target)
                    return true;
            }
        }

        /*
        for (Edge* e : v->getIncoming()){
            if (e->getReverse()->getOrig() == v && !e->getReverse()->getDest()->isVisited() && e->getReverse()->getFlow() != 0){
                s.push(e->getReverse()->getDest()->getId());
                e->getReverse()->getDest()->setVisited(true);
                e->getReverse()->getDest()->setPath(e->getReverse());
                if (e->getReverse()->getDest()->getId() == target)
                    return true;
            }
        }
         */

        s.pop();
    }
    return false;
}

/**
 * Retorna o 'bottleneck' do percurso, ou seja, o flow máximo (numero máximo de comboios) que podem atravessar o percurso, tendo em conta a capacidade minima de todas as capacidades dos edges do percurso.
 * @param target id do vértice de destino (relacionado com uma dada estação)
 * @return valor double correspondente ao bottleneck, número maximo de comboios que podem atravessar o dado percurso
 */
double Data::findBottleneck(int target) {
    Vertex* v = g.findVertex(target);
    double bottleneck = std::numeric_limits<double>::max();
    while (v->getPath() != nullptr){
        double remaining = v->getPath()->getWeight() - v->getPath()->getFlow();
        if (remaining < bottleneck)
            bottleneck = remaining;
        v = v->getPath()->getOrig();
    }
    return bottleneck;
}

/**
 * Altera o flow das edges, ou seja, o numero de comboios que podem atravessar nas linhas, tendo em consideração a bottleneck.
 * @param target id do vértice de destino (relacionado com uma dada estação)
 * @param bottleneck
 */
void Data::augmentPath(int target, double bottleneck) {
    Vertex* v = g.findVertex(target);
    while (v->getPath() != nullptr){
        v->getPath()->setFlow(v->getPath()->getFlow() + bottleneck);

        v->getPath()->getReverse()->setFlow(v->getPath()->getReverse()->getFlow() - bottleneck);

        v = v->getPath()->getOrig();
    }
}


//--------------------------
/* T2.2 */
/**
 * Determina, de todos os pares de estações, qual(ais) requer(em) maior numero de comboios, tendo em conta a capacidade de toda a rede.
 * @return par de vetores de pares de estações que requerem o valor maximo de toda a rede
 */
pair<vector<pair<Station*,Station*>>,double> Data::stationPairs(){
    double max = 0;
    Station* s1; Station* s2;
    vector<pair<Station*,Station*>> estacoes;

    for(int i1=1; i1<g.getNumVertex(); i1++){
        for (int i2=i1+1; i2<=g.getNumVertex(); i2++){
            double val = getMaxFlow(queue<int>({i1}),i2);
            if (val > max){
                estacoes.clear();
                max = val;
                s1 = g.findVertex(i1)->getStation();
                s2 = g.findVertex(i2)->getStation();
                estacoes.push_back({s1, s2});
            } else if (val == max) {
                s1 = g.findVertex(i1)->getStation();
                s2 = g.findVertex(i2)->getStation();
                estacoes.push_back({s1,s2});
            }
        }
    }
    return {estacoes, max};
}

//--------------------------
/* T2.3 */
/**
 * Indica onde se deve atribuir maiores orçamentos para a compra e manutenção de comboios e lista os municípios mais relevantes, em relação às suas necessidades de transporte.
 * @return vetor de pares de string (nomes dos municípios) e double (media de comboios que passa em cada estação do município) com maior necessidade
 */
vector<pair<string, double>> Data::topMunicipalities() {
    vector<pair<string, double>> res;
    for (const string& municipality : municipalities){
        double municipality_flow = 0;
        int station_count = 0;
        for (int i = 1; i < g.getNumVertex(); i++){
            string municipality1 = g.findVertex(i)->getStation()->getMunicipality();
            if (municipality == municipality1){
                for (int j = i + 1; j <= g.getNumVertex(); j++){
                    if (municipality1 == g.findVertex(j)->getStation()->getMunicipality()){
                        municipality_flow += getMaxFlow(queue<int>({i}), j);
                        station_count++;
                    }
                }
            }
        }
        if (municipality_flow > 0 && station_count > 0)
            res.push_back({municipality, municipality_flow / station_count});
    }
    std::sort(res.begin(), res.end(), [](const pair<string, double> p1, const pair<string, double> p2){return p1.second > p2.second;});

    return res;
}

/**
 * Indica onde se deve atribuir maiores orçamentos para a compra e manutenção de comboios e lista os distritos mais relevantes, em relação às suas necessidades de transporte.
 * @return vetor de pares de string (nomes dos distritos) e double (media de comboios que passa em cada estação do distrito) com maior necessidade
 */
vector<pair<string, double>> Data::topDistricts() {
    vector<pair<string, double>> res;
    for (const string& district : districts){
        double district_flow = 0;
        int station_count = 0;
        for (int i = 1; i < g.getNumVertex(); i++){
            string district1 = g.findVertex(i)->getStation()->getDistrict();
            if (district1 == district){
                for (int j = i + 1; j <= g.getNumVertex(); j++){
                    if (district1 == g.findVertex(j)->getStation()->getDistrict()){
                        district_flow += getMaxFlow(queue<int>({i}), j);
                        station_count++;
                    }
                }
            }
        }
        if (district_flow > 0 && station_count > 0)
            res.push_back({district, district_flow / station_count});
    }
    std::sort(res.begin(), res.end(), [](const pair<string, double> p1, const pair<string, double> p2){return p1.second > p2.second;});

    return res;
}

//-----------------------------------

/* T2.4 */
/**
 * Indica o número máximo de comboios que podem chegar simultaneamente a uma dada estação, tendo em consideração toda a rede ferroviária.
 * @param target valor inteiro correspondente ao ID da estação a considerar como destino
 * @return valor double correspondente ao número máximo de comboios que podem chegar simultaneamente à estação fornecida
 */
double Data::nrTrainsArriving(int target){
    for (Vertex* v : g.getVertexSet())
        for (Edge* e : v->getAdj())
            e->setFlow(0);

    double bottleneck;
    while (path(trainSources, target)){
        bottleneck = findBottleneck(target);
        augmentPath(target, bottleneck);
    }

    double trainsArriving = 0;
    Vertex* sink = g.findVertex(target);
    for (Edge* e : sink->getIncoming())
        trainsArriving += e->getFlow();
    return trainsArriving;
}

/**
 * Determina as estações da rede ferroviária que são fontes de comboios, neste caso, são os 'extremos' das linhas. Acrescenta-as ao vetor 'trainSources' da objeto do tipo Data.
 */
void Data::findTrainSources(){
    for (Vertex* v : g.getVertexSet())
        v->setVisited(false);

    for (Vertex* v : g.getVertexSet()) {
        if (!v->isVisited() && v->getAdj().size() == 1 && v->getIncoming().size() == 1) {
            v->setVisited(true);
            trainSources.push(v->getId());
        } else {
            for (Edge *e: v->getAdj()) {
                if (!e->getDest()->isVisited() && !v->isVisited()
                    && v->getStation()->getLine() != e->getDest()->getStation()->getLine()) {
                    if (v->getAdj().size() >= e->getDest()->getAdj().size()) {
                        v->setVisited(true);
                        trainSources.push(v->getId());
                    } else {
                        e->getDest()->setVisited(true);
                        trainSources.push(e->getDest()->getId());
                    }
                }
            }
        }
    }
}

//----------------------------------
/* T3.1 */

/**
 * Calcula o número máximo de comboios que podem viajar simultaneamente entre duas estações específicas com o custo mínimo.
 * @param source id do vértice de partida (relacionado com uma dada estação)
 * @param target id do vértice de destino (relacionado com uma dada estação)
 * @return par de valores double correspondentes ao 'bottleneck' (numero maximo de comboios que pode atravessar o percurso) e custo ,respetivamente
 */
pair<double, double> Data::maxTrainsCost(int source, int target){
    cheapestPath(source, target);

    Vertex* v = g.findVertex(target);
    double bottleneck = std::numeric_limits<double>::max();
    double cost = v->getDist();

    while (v->getPath() != nullptr){
        if (v->getPath()->getWeight() < bottleneck)
            bottleneck = v->getPath()->getWeight();
        v = v->getPath()->getOrig();
    }

    return {bottleneck, cost};
}

/**
 * ?? CONFIRMAR 1a frase
 * Percorre um dado percurso entre a estação de partida e a de chegada ('source' e 'target'), utilizando uma Breath-first-search, para atribuir as distâncias e os preços das viagens, tendo em conta se o serviço é 'Standard' ou 'Alfa'.
 * @param source id do vértice de partida (relacionado com uma dada estação)
 * @param target id do vértice de destino (relacionado com uma dada estação)
 */
void Data::cheapestPath(int source, int target) {
    for (Vertex* v : g.getVertexSet()){
        v->setVisited(false);
        v->setPath(nullptr);
        v->setDist(std::numeric_limits<double>::max());
    }

    std::queue<int> s({source});
    Vertex* source_vertex = g.findVertex(source);
    source_vertex->setVisited(true);
    source_vertex->setDist(0);
    while (!s.empty()){
        Vertex* v = g.findVertex(s.front());
        for (Edge* e : v->getAdj()) {
            double dist = e->getOrig()->getDist() + (e->getService() == "STANDARD" ? 2 : 4);
            if (!e->getDest()->isVisited()){
                e->getDest()->setDist(dist);
                e->getDest()->setVisited(true);
                e->getDest()->setPath(e);
                if (e->getDest()->getId() != target)
                    s.push(e->getDest()->getId());
            } else if (dist < e->getDest()->getDist()) {
                e->getDest()->setDist(dist);
                e->getDest()->setPath(e);
            }
        }
        s.pop();
    }
}


//----------------------------------
/* T4.1 */
//CONFIRMAR escrita
/**
 * Calcula o número máximo de comboios que podem viajar simultaneamente entre duas estações específicas numa rede de conectividade reduzida, ou seja, num subgrafo da rede ferroviária original.
 * @param source id do vértice de partida (relacionado com uma dada estação)
 * @param target id do vértice de destino (relacionado com uma dada estação)
 * @return valor double correspondende ao numero maximo de comboios que podem viajar simultaneamente entre as duas estações fornecidas na rede de comectividade reduzida
 */
double Data::getMaxFlowSub(queue<int> source, int target) {
    for (Vertex* v : g.getVertexSet()){
        for (Edge* e : v->getAdj()){
            e->setFlow(0);
        }
        /*for (Edge* e : v->getIncoming()) {
            e->setFlow(0);

            Edge* reverse = new Edge(e->getDest(), e->getOrig(), e->getWeight());
            reverse->setFlow(0);
            reverse->setReverse(e);
            e->setReverse(reverse);
        }*/
    }

    double bottleneck;
    while (pathSub(source, target)){
        bottleneck = findBottleneck(target);
        augmentPath(target, bottleneck);
    }

    double maxFlow = 0;
    Vertex* sink = g.findVertex(target);
    for (Edge* e : sink->getIncoming())
        maxFlow += e->getFlow();
    return maxFlow;
}

/**
 * Retorna verdadeiro ou falso, consoante a existencia de um percurso até ao vertex de id 'target' (estação de destino) a partir das estações de partida, rede de conectividade reduzida, ou seja, num subgrafo da rede ferroviária original. Caso exista, define esse caminho através do parâmetro 'path' dos vértices do grafo.
 * @param s queue de valores inteiros que correspondem aos ids das estações de partida
 * @param target id do vértice de destino (relacionado com uma dada estação)
 * @return valor booleano correspondente à existencia de um percurso até ao vertex de id 'target' (estação de destino) na rede de comectividade reduzida
 */
bool Data::pathSub(queue<int> s, int target) {
    for (Vertex* v : g.getVertexSet()){
        v->setVisited(false);
        v->setPath(nullptr);
    }

    while (!s.empty()){
        Vertex* v = g.findVertex(s.front());
        if (v->getId() == target){
            s.pop();
            continue;
        }
        v->setVisited(true);
        for (Edge* e : v->getAdj()) {
            if (!e->getDest()->isVisited() && e->getWeight() - e->getFlow() > 0 && e->isAvailable()) {
                s.push(e->getDest()->getId());
                e->getDest()->setVisited(true);
                e->getDest()->setPath(e);
                if (e->getDest()->getId() == target)
                    return true;
            }
        }

        /*
        for (Edge* e : v->getIncoming()){
            if (e->getReverse()->getOrig() == v && !e->getReverse()->getDest()->isVisited() && e->getReverse()->getFlow() != 0){
                s.push(e->getReverse()->getDest()->getId());
                e->getReverse()->getDest()->setVisited(true);
                e->getReverse()->getDest()->setPath(e->getReverse());
                if (e->getReverse()->getDest()->getId() == target)
                    return true;
            }
        }
         */

        s.pop();
    }
    return false;
}
//100->90 -10%
//3->0 -100%
//T4.2
/**
 * Compara dois objetos do tipo Result, em relação ao seu parâmetro 'dif'. Caso esse parâmetro seja igual, verifica o parâmetro 'sumFlow'. É utilizada como comparador numa função 'sort'.
 * @param r1 objeto do tipo result a comparar
 * @param r2 objeto do tipo result a comparar
 * @return valor booleano consoante a comparação dos dois objetos Result
 */
bool comp(Result r1, Result r2){
    return r1.dif > r2.dif || (r1.dif == r2.dif && r1.sumFlow > r2.sumFlow );
}

/**
 * Determina as top K estações mais afetadas por falhas nos segmentos da rede ferroviária.
 * @param k valor inteiro que determina o número de estações listadas
 * @return vetor de objetos Result correspondentes às top estações mais afetadas
 */
vector<Result> Data::topAffected(int k){
    vector<Result> res;
    Station * s;
    double sumFlow, sumFlowSub;
    double dif;

    for(auto  v1: g.getVertexSet()){
        s = v1->getStation();
        if (v1->getAdj().size() != 0) {
            sumFlow = getMaxFlow(trainSources, v1->getId());
            sumFlowSub = getMaxFlowSub(trainSources, v1->getId());

            dif = ((sumFlow - sumFlowSub) * 1.0 / (sumFlow) * 1.0) * 100.0; //%
            res.push_back({s, dif, sumFlow, sumFlowSub});
        }
    }
    sort(res.begin(), res.end(), comp);
    res.erase(res.begin()+k,res.end());
    return res;
}

const string &Data::getStations() const {
    return stations;
}

const string &Data::getNetwork() const {
    return network;
}


