#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <sstream>

using namespace std;

/*
 *
 */

string transformaMatrizString(vector< vector<int> > matriz){

    int a;
    int b;
    string matrizstring = "";
    for(a=0; a<4; a++){
        for(b=0; b<4;b++){
            ostringstream convert;
            convert << matriz[a][b];
            string elemento = convert.str();
            matrizstring += elemento;
            matrizstring += " ";
        }
    }
    return matrizstring;
}

vector< vector<int> > transformaStringMatriz(string matriz){
    vector< vector<int> > retorno(4, vector<int>(4));
    std::stringstream sstr(matriz);
    int x = 0;
    int y = 0;
    int i;
    while (sstr >> i){
        if(y==4){
            x += 1;
            y= 0 ;
        }
        retorno[x][y] = i;
        y++;
    }
    return retorno;
}

std::pair<int, int> localizazero(vector< vector<int> >matriz){
    for (int x=0; x < 4; x++){
        for (int y=0; y < 4; y++){
            if (matriz[x][y] == 0){
                std::pair<int, int> zerox;
                zerox = std::make_pair(x, y);
                return zerox;
            }
        }
     }
}

int diferencaMatriz(vector< vector<int> >matriz){
    vector< vector<int> > original                   = {{1, 5, 9, 13},
                                                        {2, 6, 10, 14},
                                                        {3, 7, 11, 15},
                                                        {4, 8, 12, 0}};

    vector< vector<int> > original2                  = {{1, 4, 7},
                                                        {2, 5, 8},
                                                        {3, 6, 0}};


    int dif = 0;
    int a;
    int b;
    for (a=0; a<4; a++){
        for(b=0; b<4; b++){
            if (matriz[a][b] == 0){
                continue;
            }
            if (original[a][b] != matriz[a][b]){
                dif++;
            }
        }
    }
    return dif;

}









void principal(vector< vector<int> > matrizatual, int movimentos){
    std::unordered_map<string,int> closed_list;
    std::unordered_map<string,int> javistos;
    std::multimap<int,std::pair<vector< vector<int> >, int> > open_list;


    string pai;
    int difmatrizatual = diferencaMatriz(matrizatual);
    std::pair<vector< vector<int> >, int> segundoargumento;
    segundoargumento = std::make_pair(matrizatual, 0);
    std::pair<int, std::pair<vector< vector<int> >, int> > inserir;
    inserir = std::make_pair(difmatrizatual, segundoargumento);

    open_list.insert(inserir);
    int counter = 1;

    while(!open_list.empty()){
        cout<<"Arvores Processacadas: "<<counter<<"\n";
        counter++;
        std::multimap<int,std::pair<vector< vector<int> >, int> >::iterator multiatual = open_list.begin();
        std::pair<vector< vector<int> >, int>  par2 = multiatual->second;
        vector< vector<int> > matrizatualx = par2.first;
        int difmatrizatual = diferencaMatriz(matrizatualx);
        int custoatual = par2.second;
        string stringatual = transformaMatrizString(matrizatualx);
        //LOCALIZA O ZERO
        std::pair<int, int> zerot = localizazero(matrizatualx);
        int x = zerot.first;
        int y = zerot.second;
        int x0 = x-1;
        int x1 = x+1;
        int y0 = y-1;
        int y1 = y+1;

        cout<<"Dif matriz atual: "<<difmatrizatual<<"\n";
        cout<<"Custo desse no: "<<custoatual<<"\n";
        cout<<"Custo TOTAL: "<<difmatrizatual + custoatual<<"\n";
        cout<<"Custo TOTAL 2: "<<multiatual->first<<"\n\n";
        /*
        typedef std::multimap<int,std::pair<vector< vector<int> >, int> >::iterator Iter;
        for (Iter it = open_list.begin(); it != open_list.end(); ) {
                int ft = it->first;
                std::pair<vector< vector<int> >, int>  ft2 = it->second;
                int ft3 = ft2.second;
                cout<<"Custo teste: "<<ft<<" Altura: "<<ft3<<"\n";
                it++;
        }
        */


        if (difmatrizatual== 0){
            cout<<"Custo: "<<custoatual<<"\n";
            break;
        }

        if(x0>=0){

            vector< vector<int> > matriz(4, vector<int>(4));


            matriz = matrizatualx;
            matriz[x][y] = matrizatualx[x0][y];
            matriz[x0][y] = matrizatualx[x][y];
            string possibilidade = transformaMatrizString(matriz);

            std::unordered_map<string,int>::iterator got1 = closed_list.find(possibilidade);
            std::unordered_map<string,int>::iterator visto = javistos.find(possibilidade);
            int custoateaqui = diferencaMatriz(matriz) + custoatual + 1;


            if (got1==closed_list.end()){
                if (visto==javistos.end()){




                    std::pair<vector< vector<int> >, int> segundoargumento;
                    segundoargumento = std::make_pair(matriz, custoatual + 1);
                    std::pair<int, std::pair<vector< vector<int> >, int> > inserir;
                    inserir = std::make_pair(custoateaqui, segundoargumento);
                    open_list.insert(inserir);

                    std::pair<string, int> vistoadicionar;
                    vistoadicionar = std::make_pair(possibilidade, custoateaqui);
                    javistos.insert(vistoadicionar);
                }
                else{
                    /*
                    cout<<"Repetido!"<<"\n";
                    cout<<"Valor registrado: "<<visto->second<<"\n";
                    cout<<"Valor atual: "<<custoateaqui<<"\n";
                    int opt;
                    cin>>opt;
                    if (opt== 1){
                        break;
                    }
                    */
                }

            }
        }
        if(x1<=3){
            vector< vector<int> > matriz(4, vector<int>(4));
            matriz = matrizatualx;
            matriz[x][y] = matrizatualx[x1][y];
            matriz[x1][y] = matrizatualx[x][y];
            string possibilidade = transformaMatrizString(matriz);
            std::unordered_map<string,int>::iterator got1 = closed_list.find(possibilidade);
            std::unordered_map<string,int>::iterator visto = javistos.find(possibilidade);
            int custoateaqui = diferencaMatriz(matriz) + custoatual + 1;

            if (got1==closed_list.end()){
                if (visto==javistos.end()){




                    std::pair<vector< vector<int> >, int> segundoargumento;
                    segundoargumento = std::make_pair(matriz, custoatual + 1);
                    std::pair<int, std::pair<vector< vector<int> >, int> > inserir;
                    inserir = std::make_pair(custoateaqui, segundoargumento);
                    open_list.insert(inserir);

                    std::pair<string, int> vistoadicionar;
                    vistoadicionar = std::make_pair(possibilidade, custoateaqui);
                    javistos.insert(vistoadicionar);
                }
                else{
                    /*
                    cout<<"Repetido!"<<"\n";
                    cout<<"Valor registrado: "<<visto->second<<"\n";
                    cout<<"Valor atual: "<<custoateaqui<<"\n";
                    int opt;
                    cin>>opt;
                    if (opt== 1){
                        break;
                    }
                    */
                }

            }
        }
        if(y0>=0){
            vector< vector<int> > matriz(4, vector<int>(4));
            matriz = matrizatualx;
            matriz[x][y] = matrizatualx[x][y0];
            matriz[x][y0] = matrizatualx[x][y];
            string possibilidade = transformaMatrizString(matriz);
            std::unordered_map<string,int>::iterator got1 = closed_list.find(possibilidade);
            std::unordered_map<string,int>::iterator visto = javistos.find(possibilidade);
            int custoateaqui = diferencaMatriz(matriz) + custoatual + 1;

            if (got1==closed_list.end()){
                if (visto==javistos.end()){




                    std::pair<vector< vector<int> >, int> segundoargumento;
                    segundoargumento = std::make_pair(matriz, custoatual + 1);
                    std::pair<int, std::pair<vector< vector<int> >, int> > inserir;
                    inserir = std::make_pair(custoateaqui, segundoargumento);
                    open_list.insert(inserir);

                    std::pair<string, int> vistoadicionar;
                    vistoadicionar = std::make_pair(possibilidade, custoateaqui);
                    javistos.insert(vistoadicionar);
                }
                else{
                    /*
                    cout<<"Repetido!"<<"\n";
                    cout<<"Valor registrado: "<<visto->second<<"\n";
                    cout<<"Valor atual: "<<custoateaqui<<"\n";
                    int opt;
                    cin>>opt;
                    if (opt== 1){
                        break;
                    }
                    */
                }

            }
        }
        if(y1<=3){
            vector< vector<int> > matriz(4, vector<int>(4));
            matriz = matrizatualx;
            matriz[x][y] = matrizatualx[x][y1];
            matriz[x][y1] = matrizatualx[x][y];
            string possibilidade = transformaMatrizString(matriz);
            std::unordered_map<string,int>::iterator got1 = closed_list.find(possibilidade);
            std::unordered_map<string,int>::iterator visto = javistos.find(possibilidade);
            int custoateaqui = diferencaMatriz(matriz) + custoatual + 1;

            if (got1==closed_list.end()){
                if (visto==javistos.end()){




                    std::pair<vector< vector<int> >, int> segundoargumento;
                    segundoargumento = std::make_pair(matriz, custoatual + 1);
                    std::pair<int, std::pair<vector< vector<int> >, int> > inserir;
                    inserir = std::make_pair(custoateaqui, segundoargumento);
                    open_list.insert(inserir);

                    std::pair<string, int> vistoadicionar;
                    vistoadicionar = std::make_pair(possibilidade, custoateaqui);
                    javistos.insert(vistoadicionar);
                }
                else{
                        /*
                    cout<<"Repetido!"<<"\n";
                    cout<<"Valor registrado: "<<visto->second<<"\n";
                    cout<<"Valor atual: "<<custoateaqui<<"\n";
                    int opt;
                    cin>>opt;
                    if (opt== 1){
                        break;
                    }
                    */
                }

            }
        }

        if (closed_list.empty()){
            string atualstring = transformaMatrizString(matrizatualx);
            std::pair<std::string,int> estadofinalizado;
            estadofinalizado = make_pair(atualstring, 0);
            closed_list.insert(estadofinalizado);
            }
        else{
            string atualstring = transformaMatrizString(matrizatualx);
            std::pair<std::string,int> estadofinalizado;
            estadofinalizado = make_pair(atualstring, custoatual + 1);
            closed_list.insert(estadofinalizado);
        }

        open_list.erase(multiatual);
    }

}




int main(int argc, char** argv) {

    vector< vector<int> > teste2 = {{0, 13, 9, 2},
                                    {4, 5, 8, 6},
                                    {3, 7, 12, 10},
                                    {15, 1, 14, 11}};

    vector< vector<int> > caso1 = {{1, 5, 9, 13},
                                     {6, 3, 10, 14},
                                     {4, 11, 0, 15},
                                     {7, 2, 8, 12}};

    vector< vector<int> > caso2 = {{1, 6, 0, 11},
                                   {2, 9, 13, 5},
                                   {3, 7, 14, 10},
                                   {4, 8, 12, 15}};

    vector< vector<int> > caso3 = {{9, 8, 0, 14},
                                   {7, 6, 5, 1},
                                   {2, 4, 11, 10},
                                   {3, 12, 13, 15}};

    vector< vector<int> > caso4 = {{1, 13, 7, 10},
                                    {2, 0, 12, 11},
                                    {3, 14, 6, 9},
                                    {8, 4, 5, 15}};

    vector< vector<int> > caso5 = {{4, 7, 0, 13},
                                   {5, 9, 10, 14},
                                   {6, 11, 3, 1},
                                   {8, 2, 15, 12}};

    principal(caso2, 0);
    return 0;
}
