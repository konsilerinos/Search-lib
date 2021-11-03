#include "search.h"
#include "view.h"

/**
 * @brief Точка входа
 * @return 0 - код успешного завершения
 */
int main() {

    Search search;

    search.RunTimeTest(100);
    search.RunTimeTest(500);
    search.RunTimeTest(1000);

    View::Print("Press <Enter> to continue...");

    return 0;
}
