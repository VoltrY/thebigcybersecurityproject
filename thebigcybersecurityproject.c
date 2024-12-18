#include <stdio.h>
#include <string.h>

int main() {
    // Satırları okumak için kullanılacak tampon değişken
    char satirTampon[256];
    //unsigned  -256 , +255
    // signed 0 , +256
    //Dosyadan okunan her bir satır geçici olarak burada saklanır. sonrada bu satır satirDizi dizisine kopyalanır

    char *satirDizi[60]; // Satırları dinamik olarak tutmak için bir dizi

    // POİNTER KULLANIM AMACI : her satırdaki verinin değerini olduğu değere eşitler ve dinamik bir veri tutumu sağlar.
    /*
    *    Örneğin;
    *    12345
    *    1234
    *    123
    *    12
    *    Dinamik veri tutumunu her satıra kendi değeri kadar yer ayırarak bellekten tasarruf etmiş oluruz.
    */
    //strdup ve satirTampon değişkenlerindeki her satırın kopyası bu diziye aktarılır her satırın adresi burda tutulur.
    int satirSayac = 0; // Okunan satır sayısını takip eder
    // her satır okunduğunda bir arttırılır ve satirDizi değişkeninde uygun bir yere yerleştirilir.

    // Kaynak dosyayı aç
    FILE *girisDosya = fopen("giris.txt", "r");
    if (girisDosya == NULL) {
        printf("Dosya açılamadı. Dosya dizinini kontrol ediniz.\n");
        return 1;
    }123123123 
    // Dosyayı satır satır oku
    while (fgets(satirTampon, sizeof(satirTampon), girisDosya) != NULL) { //fgets değerleri string olarak okur
        long unsigned int satirUzunluk = strlen(satirTampon); //
        // satirTampon içindeki satır uzunluğunu hesaplayıp satirUzunluk'a atar
        if (satirTampon[satirUzunluk - 1] == '\n') { // satirUzunlukdan fgets'in eklediği \0'ı sileriz. ve \n var mı diye bakıyoruz
            satirTampon[satirUzunluk - 1] = '\0'; // var olduğu takdirde fgets'in koyduğu \n yerine \0 yani NULL koyarız
        }
        // Okunan satırı satirDizi dizisine kopyala
        satirDizi[satirSayac] = strdup(satirTampon); // String bir değişkene direkt eşitlenemediği için string dupplicate kullanıyoruz.
        satirSayac++;
    } 
    fclose(girisDosya);

    // Çıktı dosyasını aç
    FILE *casusDosya = fopen("casus.txt", "w");
    if (casusDosya == NULL) {
        printf("Dosya açılamadı. Dosya dizinini kontrol ediniz\n");
        return 1;
    }

    // Aynı olan satırları ve sayısını bul ve çıktı dosyasına yaz
    for (int i = 0; i < satirSayac; i++) {
        int k = 1; // 1'den başlatırız çünkü eğer casusun kaç kere çıkıp girdiğini bulmak istersek 0 1 2 3 olacağından 3 cevabını almış oluruz fakat 1'den başlatırsak 4 cevabını alırız
        if (satirDizi[i] == NULL) 
            continue; // Daha önce işlenmiş satırları atla
        for (int j = i + 1; j < satirSayac; j++) {
            if (satirDizi[j] != NULL && strcmp(satirDizi[i], satirDizi[j]) == 0) { //strcmp == 0 ise eşit, 1 ise eşit değil
                k += 1; // k'yı arttırırız çünkü casusumuz bulundu.
                satirDizi[j] = NULL; // İşlenmiş olarak işaretleriz.
            }
        }
        if (k > 1) {
            fprintf(casusDosya, "Casus'un TC Kimlik Numarası: %s\n", satirDizi[i]); // %s = string demektir.
        }
        

    }

    fclose(casusDosya);
    printf("Olası casuslar casus.txt dosyasına yazıldı.");

    return 0;
}
