#include <stdio.h>
#include <string.h>

int main() {
    // Satırları okumak için kullanılacak tampon değişken
    char satirTampon[256];
    //Dosyadan okunan her bir satır geçici olarak burada saklanır. sonrada bu satır satirDizi dizisine kopyalanır

    char *satirDizi[100]; // Satırları dinamik olarak tutmak için bir dizi
    // POİNTER KULLANIM AMACI
    //strdup ve satirTampon değişkenlerindeki her satırın kopyası bu diziye aktarılır her satırın adresi burda tutulur.
    int satirSayac = 0; // Okunan satır sayısını takip eder
    // her satır okunduğunda bir arttırılır ve satirDizi değişkeninde uygun bir yere yerleştirilir.

    // Kaynak dosyayı aç
    FILE *girisDosya = fopen("giris.txt", "r");
    if (girisDosya == NULL) {
        printf("Dosya açılamadı. Dosya dizinini kontrol ediniz.\n");
        return 1;
    }
    // Dosyayı satır satır oku
    while (fgets(satirTampon, sizeof(satirTampon), girisDosya) != NULL) {
        size_t satirUzunluk = strlen(satirTampon); // 2139842143294
        // satirTampon içindeki satır uzunluğunu hesaplayıp satirUzunluk'a atar
        if (satirTampon[satirUzunluk - 1] == '\n') {
            satirTampon[satirUzunluk - 1] = '\0';
        }

        // Okunan satırı satirDizi dizisine kopyala
        satirDizi[satirSayac] = strdup(satirTampon);
        if (satirDizi[satirSayac] == NULL) {
            printf("Boş satır veya Satır okunamadı.\n");
            continue;
        }
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
        int k = 1;
        if (satirDizi[i] == NULL) continue; // Daha önce işlenmiş satırları atla

        for (int j = i + 1; j < satirSayac; j++) {
            if (satirDizi[j] != NULL && strcmp(satirDizi[i], satirDizi[j]) == 0) { //strcmp == 0 ise eşit, 1 ise eşit değil
                k += 1;
                satirDizi[j] = NULL; // İşlenmiş olarak işaretle
            }
        }
        if (k > 1) {
            fprintf(casusDosya, "Casus'un TC Kimlik Numarası: %s\n", satirDizi[i]);
        }
    }
    fclose(casusDosya);
    printf("Olası casuslar casus.txt dosyasına yazıldı.");

    return 0;
}


