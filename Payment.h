//Після 3 годин помилок, які вибивались, через те, що структура була тільки в Modules.h, було зроблене рішення зробити ще один хедер, чисто для структури, таким чином програма перестала вибивати помилку
fndef PAYMENT_H
#define PAYMENT_H

typedef struct {
    char surname[50];
    int account_number;
    int date[3];
    float amount;
} Payment;

#endif  // PAYMENT_H
