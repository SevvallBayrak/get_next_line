# 📄 get_next_line - Satır Satır Dosya Okuma

`get_next_line`, bir dosyadan satır satır veri okumayı sağlayan bir fonksiyondur. Her çağrıldığında bir sonraki satırı döner ve C dilinde **statik değişken kullanımı**, **buffer yönetimi**, **file descriptor (fd)** ile çalışma gibi birçok ileri konuyu öğretmeyi amaçlar.

---

## 🎯 Projenin Amacı

C'de satır satır okuma işlemi `fgets`, `getline` gibi fonksiyonlarla yapılabilir. Bu projede ise bunları **kendi başımıza sıfırdan** yazmamız beklenir. Bu sayede:

- Sistem çağrısı (`read`) kullanımı
- Bellek yönetimi (`malloc`, `free`)
- Statik değişkenlerle durum koruma (stateful fonksiyonlar)

konularında uzmanlaşmak hedeflenir.

---

## 🧠 Neler Öğrendim?

### 📁 Dosya Okuma ve `read()`
- Dosya descriptor (int fd) ile düşük seviyeli dosya okuma mekanizmasını öğrendim.
- Aynı fonksiyonun hem dosya hem de `stdin` (terminal girdisi) ile nasıl çalıştırılacağını anladım.

### 🧮 Statik Değişken ve State Management
- `static` değişken kullanarak fonksiyonlar arası veri saklamayı öğrendim.
- Bir dosyadan satır satır okumada state'in nasıl korunduğunu kavradım.

### 🧵 Dinamik Buffer Yönetimi
- `BUFFER_SIZE` değişkenine göre dinamik olarak satır birleştirme (join), parçalara ayırma (split), kopyalama işlemlerini gerçekleştirdim.
- Bellek sızıntılarını önlemek için manuel `malloc/free` yönetimi uyguladım.

### ⚠️ Edge Case Yönetimi
- Boş dosyalar, sadece `\n` içeren satırlar, EOF'ta newline olmayan son satır gibi durumları doğru şekilde ele aldım.
- Hatalı fd, invalid `BUFFER_SIZE` gibi durumlar için güvenli kontroller ekledim.

---

## 🧪 Kullanım

```c
#include "get_next_line.h"

int main(void)
{
    char *line;
    int fd = open("dosya.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
}

🛠️ Derleme
Makefile ile kolayca derleyebilirsin:
make        # get_next_line.a üretir
make clean  # .o dosyalarını siler
make fclean # tüm çıkışları temizler
make re     # yeniden derler
