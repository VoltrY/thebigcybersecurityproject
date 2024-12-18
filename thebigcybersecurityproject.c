#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    // Satırları okumak için kullanılacak tampon değişken
    char satirTampon[256];

    // Dinamik bir dizi tutmak için
    char **satirDizi = NULL; // İlk başta NULL, bellek ayırılana kadar

    int satirSayac = 0; // Okunan satır sayısını takip eder

    // Kaynak dosyayı aç
    FILE *girisDosya = fopen("giris.txt", "r");
    if (girisDosya == NULL) {
        printf("Dosya açılamadı. Dosya dizinini kontrol ediniz.\n");
        return 1;
    }

    // Dosyayı satır satır oku ve dinamik diziye aktar
    while (fgets(satirTampon, sizeof(satirTampon), girisDosya) != NULL) {
        // Satırın uzunluğunu hesapla
        size_t satirUzunluk = strlen(satirTampon);

        // '\n' karakterini sonundan çıkar
        if (satirTampon[satirUzunluk - 1] == '\n') {
            satirTampon[satirUzunluk - 1] = '\0';
        }

        // SatırDizi'yi genişletmek için yeniden bellek ayır
        satirDizi = realloc(satirDizi, (satirSayac + 1) * sizeof(char *));
        if (satirDizi == NULL) {
            printf("Bellek ayırma hatası.\n");
            return 1;
        }

        // Dinamik bellek ayır ve satırı kopyala
        satirDizi[satirSayac] = strdup(satirTampon);
        if (satirDizi[satirSayac] == NULL) {
            printf("Bellek ayırma hatası.\n");
            return 1;
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
        int k = 1; // Casus sayısını başlat
        if (satirDizi[i] == NULL)
            continue; // Daha önce işlenmiş satırları atla

        for (int j = i + 1; j < satirSayac; j++) {
            if (satirDizi[j] != NULL && strcmp(satirDizi[i], satirDizi[j]) == 0) {
                k += 1;
                satirDizi[j] = NULL; // İşlenmiş olarak işaretleriz.
            }
        }

        // Aynı olan satırları çıktıya yaz
        if (k > 1) {
            fprintf(casusDosya, "Casus'un TC Kimlik Numarası: %s\n", satirDizi[i]);
        }
    }

    fclose(casusDosya);
    printf("Olasi casuslar casus.txt dosyasina yazildi.");

    // Bellek serbest bırakma işlemi
    for (int i = 0; i < satirSayac; i++) {
        free(satirDizi[i]);
    }
    free(satirDizi); // Toplam dinamik bellek serbest bırakma

    return 0;
}
