#include <stdio.h>
#include <ctype.h>
/* Code to check if a letter is a vowel or consonant */

void revisarLetra(char letra)
{
    /* Check if input is a letter of the alphabet */
    if (isalpha(letra) != 0){
        /* Change letter to lowercase */
        letra = tolower(letra);
        /* We define all posible vowels*/
        if( letra == 'a' || letra == 'e' || letra == 'i' || letra == 'o' || letra == 'u'){
        printf("La letra '%c' es una vocal.\n", letra);
        }
        else{
        printf("La letra '%c' es una consonante.\n", letra);
        }
    }
    else{
        printf("El caracter ingresado no es una letra del abecedario.\n");
    }
}

int main()
{
    char letra;
    printf("Por favor ingrese una letra del abecedario. Si ingresa mas de una letra, se leera solo la primera\n");
    /* Read user's input, getchar() only reads one letter (char) */
    letra = getchar();
    revisarLetra(letra);
    return 0;
}