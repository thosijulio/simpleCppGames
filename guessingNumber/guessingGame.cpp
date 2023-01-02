/*
    Padrao para adição de bibliotecas em C++: 
        "#include" e o nome da biblioteca que será utilizada entre "<>"
*/
// iostream é uma biblioteca que possui métodos para o fluxo de entra e saída de dados.
#include<iostream>

#include<cstdlib>
/* marcador para uso das funções padrão de C++ = "using namespace std". Seu uso não é aconselhavel por alguns motivos,
   incluindo os debatidos nessa questão no StackOverflow: https://stackoverflow.com/questions/1452721/why-is-using-namespace-std-considered-bad-practice
*/

// main: Função que guarda todo o código que será executado
// pelo compilador quando abrir este arquivo.
int main(void) {
    // Método para gerar um número aleatório entre 1 e 100;
    srand(time(NULL));
    const int SECRET_NUMBER = (rand() % 100) + 1;


    int guessingNumber;
    bool userIsWrong = true;
    int triesLeft = 5;
    float userPoints = 1000;
    

    // variáveis que ajudam a fazer a conta chegar a 0 caso o usuário digite a pior combinação possível de resultado para cada nível escolhido.
    float multipliedByDificulty = 0;
    float sumByDificulty = 0;
    int dificulty;

    // cout é a função padrão do C++ que lida com as saídas de um programa pelo terminal. cin é a função que lida com as entradas do usuário.
    std::cout << "****************************\n";
    std::cout << "Welcome to the guessing game!" << std::endl;
    std::cout << "****************************\n\n";
    std::cout << "First of all, select your dificulty:" << std::endl;
    std::cout << "1. Extreme (3 chances);" << std::endl;
    std::cout << "2. Hard (5 chances);" << std::endl;
    std::cout << "3. Medium (8 chances);" << std::endl;
    std::cout << "4. Easy (12 chances);" << std::endl;
    std::cout << "5. Very Easy (15 chances)\n\n";
    
    std::cout << "Option: " << std::endl;
    std::cin >> dificulty;
    int numbersTriedByuser[dificulty];

    // bloco que altera o sistema de pontuação e o número de tentativas de acordo com a dificuldade escolhida pelo usuário.
    switch (dificulty) {
        case 1:
            triesLeft = 3;
            multipliedByDificulty = 3.4;
            sumByDificulty = 2.667;
            break;

        case 2:
            triesLeft = 5;
            multipliedByDificulty = 2.1;
            sumByDificulty = 7; 
            break;

        case 3:
            triesLeft = 8;
            multipliedByDificulty = 1.278;
            sumByDificulty = 1; 
            break;
        
        case 4:
            triesLeft = 12;
            multipliedByDificulty = 0.857;
            sumByDificulty = 0.667; 
            break;
        
        case 5:
            triesLeft = 15;
            multipliedByDificulty = 0.68;
            sumByDificulty = 0.33339;
            break;

        default:
            throw std::invalid_argument("Insert a integer between 1 and 5 to select dificulty.");
            break;
    }

    // loop para ficar rodando o jogo enquanto o usuario nao acertar e ainda estiver tentativar disponiveis.
    while(userIsWrong and triesLeft) {

        // Pega o numero digitado pelo usuario e em seguida coloca no array de numeros ja escolhidos.
        std::cout << "Type a number between 1 and 100: ";
        std::cin >> guessingNumber;
        numbersTriedByuser[triesLeft - triesLeft] = guessingNumber;

        if(SECRET_NUMBER == guessingNumber) {
        std::cout << "Congrats, You win!" << std::endl;
        std::cout.precision(2);
        std::cout << std::fixed;
        std::cout << "Points: " << userPoints << std::endl;
        userIsWrong = false;
        } else if(guessingNumber > SECRET_NUMBER) {
            --triesLeft;
            std::cout << "Sorry, the number choised was higher than the secret number. You have " << triesLeft << " tries left." << std::endl;
        } else if (guessingNumber < SECRET_NUMBER) {
            --triesLeft;
            std::cout << "Sorry, the number choised was lower than the secret number. You have " << triesLeft << " tries left." << std::endl;
        }

        // Bloco que faz a checagem e altera a pontuação do usuario.
        // se o usuário digitar o número mais longe o possível do correto (numero escolhido = 1; usuário digita 5 vezes o numero 100) resulta em uma pontuação zerada.+
        if(userPoints - abs((SECRET_NUMBER - guessingNumber) * multipliedByDificulty) + sumByDificulty < userPoints) {
            userPoints = userPoints - abs((SECRET_NUMBER - guessingNumber) * multipliedByDificulty) + sumByDificulty;
        } else {
            userPoints = userPoints - ((userPoints - abs((SECRET_NUMBER - guessingNumber) * multipliedByDificulty) + sumByDificulty) - userPoints);
        }
    }

    if(userIsWrong) {
        std::cout.precision(2);
        std::cout << std::fixed;
        std::cout << "Sorry, you lose. Your pontuation was: " << userPoints << std::endl;
    }
}