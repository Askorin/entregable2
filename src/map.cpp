#include "../inc/map.h"

size_t HashMap::hashUsername(std::string username) {
    /* Calcularemos el haschode del string x_0 ... x_d como el polinomio
     * x_d * alpha ^ 0 + x_d-1 * alpha^1 ... x_0 * alpha ^d
     */

    /* Ojo que esto puede hacer overflow */

    /* Utilizamos alpha = 33 como recomendado en el ppt del curso. */
    /* se calcula de manera recursiva como: */
    size_t alpha = 33;
    unsigned long long sum = 0;
    
    for (auto &ch : username) {
        sum = (alpha * sum + (int) ch);
    }


    /* mult mod prime con a, b menores a m (tamaño de la tabla, número primo, quizás). */
    /* Para N = 49157 */
    size_t a = 45382, b = 11923;
    
    return (a * sum + b) % N;

}

size_t HashMap::hashId(unsigned long long id) {
    /* mult mod prime con a, b menores a m (tamaño de la tabla, número primo, quizás). */
    size_t a = 45382, b = 11923;
    
    return (a * id + b) % N;

}

