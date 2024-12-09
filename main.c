#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SATIR_UZUNLUGU 256  // Satır uzunluğu sınırı
#define KIMLIK_UZUNLUGU 11  // Kimlik numarası uzunluğu

// Dinamik bellek yönetimi için düğüm yapısı
typedef struct Kimlik {
    char numara[KIMLIK_UZUNLUGU + 1];
    int tekrar_sayisi;
    struct Kimlik *sonraki;
} Kimlik;

Kimlik* kimlik_bul_veya_ekle(Kimlik **liste, char *numara) {
    Kimlik *gecici = *liste;

    // Var olan kimlik numarasını bul
    while (gecici != NULL) {
        if (strcmp(gecici->numara, numara) == 0) {
            gecici->tekrar_sayisi++;
            return gecici;
        }
        gecici = gecici->sonraki;
    }

    // Yeni bir kimlik numarası ekle
    Kimlik *yeni = (Kimlik*)malloc(sizeof(Kimlik));
    strcpy(yeni->numara, numara);
    yeni->tekrar_sayisi = 1;
    yeni->sonraki = *liste;
    *liste = yeni;

    return yeni;
}

void kimlikleri_temizle(Kimlik *liste) {
    while (liste != NULL) {
        Kimlik *silinecek = liste;
        liste = liste->sonraki;
        free(silinecek);
    }
}

int main() {
    FILE *giris_dosyasi, *cikis_dosyasi;
    char satir[SATIR_UZUNLUGU];
    Kimlik *kimlik_listesi = NULL;

    // Giriş dosyasını aç
    giris_dosyasi = fopen("/home/voltry/CLionProjects/thebigcybersecurityproject/giris.txt", "r");
    if (giris_dosyasi == NULL) {
        perror("giris.txt açılamadı");
        return 1;
    }

    // Kimlik numaralarını oku
    while (fgets(satir, SATIR_UZUNLUGU, giris_dosyasi)) {
        // Satır sonundaki yeni satır karakterini temizle
        satir[strcspn(satir, "\n")] = '\0';

        // Kimlik numarası uzunluğunu kontrol et
        if (strlen(satir) == KIMLIK_UZUNLUGU) {
            kimlik_bul_veya_ekle(&kimlik_listesi, satir);
        }
    }
    fclose(giris_dosyasi);

    // Çıkış dosyasını oluştur
    cikis_dosyasi = fopen("/home/voltry/CLionProjects/thebigcybersecurityproject/casus.txt", "w");
    if (cikis_dosyasi == NULL) {
        perror("casus.txt açılamadı");
        kimlikleri_temizle(kimlik_listesi);
        return 1;
    }

    fprintf(cikis_dosyasi, "2'den fazla tekrar eden kimlik numaraları:\n");

    // Tekrar eden kimlik numaralarını yaz
    Kimlik *gecici = kimlik_listesi;
    while (gecici != NULL) {
        if (gecici->tekrar_sayisi > 2) {
            fprintf(cikis_dosyasi, "%s (tekrar sayısı: %d)\n", gecici->numara, gecici->tekrar_sayisi);
        }
        gecici = gecici->sonraki;
    }

    fclose(cikis_dosyasi);

    // Dinamik bellek temizliği
    kimlikleri_temizle(kimlik_listesi);

    printf("İşlem tamamlandı. Tekrar eden kimlik numaraları casus.txt dosyasına kaydedildi.\n");
    return 0;
}
