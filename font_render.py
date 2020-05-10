import string

from PIL import ImageFont

FONT_FILE = 'intput.ttf'  # Файл с шрифтом
FONT_SIZE = 20  # Размер шрифта (не в пикселях а в точках)

OUTPUT_FILENAME = '/tmp/sample.c'


def to_matrix(s, font):
    mask = font.getmask(s, '1')
    w, h = mask.size
    return [[0 if mask.getpixel((x, y)) == 0 else 1 for x in range(w)]
            for y in range(h)]


# Загружаем шрифт
font = ImageFont.truetype(FONT_FILE, size=FONT_SIZE)

# Все видимые символы ASCII + пробел
all_chars = string.digits + string.ascii_letters + string.punctuation + ' '
# print(all_chars)

# Проверяем что все символы имеют одну и ту же ширину
sizes = set(map(lambda c: font.getsize(c)[0], all_chars))
assert len(sizes) == 1

char_width = list(sizes)[0]  # Длина одного символа

# Строим матрицу, кодирующую всю строку
m = to_matrix(all_chars, font)

# Проверим, что размер матрицы кратен количеству символов и соотвествует
# размеру одного символа
assert len(m[0]) % len(all_chars) == 0
assert len(m[0]) / len(all_chars) == char_width

# Создаем словарь, где ключ - символ, а значение - матрица для него
chars_bitmaps = dict()
# Подготовим матрицу для упрощенного извлечения (транспонируем)
mm = list(zip(*m))
for i, c in enumerate(all_chars):
    # Поскольку кодировалась строка целиком, то символы находятся в тойже
    # последовательности что и в строке, воспользуемся этим

    # Деляем срез от i позиции на char_width пикселей и транспонируем опять
    char_matrix = list(zip(*mm[i * char_width: (i + 1) * char_width]))
    chars_bitmaps[c] = char_matrix

# Создаем файл для использования в программе на Си
output = list()  # Построчно формируем

# 1. Записываем размеры матрицы символа
output.append('const unsigned CHAR_HEIGHT = {};'.format(len(m)))
output.append('const unsigned CHAR_WIDTH = {};'.format(char_width))

output.append('')  # Пустая строка

# Добавляем typedef для удобства чтения кода
output.append('typedef unsigned char Matrix[{}][{}];'.format(len(m),
                                                             char_width))
output.append('')  # Пустая строка
output.append('')  # Пустая строка

# 2. Формируем матрицы для каждого символа
for c in sorted(all_chars):
    output.append("// '{}'".format(c))
    output.append('static Matrix matrix_{:02x} = {{'.format(ord(c)))
    for line in chars_bitmaps[c]:
        output.append('  {{ {}, }},'.format(', '.join(map(str, line))))
    output.append('};')
    output.append('')  # Пустая строка

# 3. Формируем массив символов с указателями на соотвествующие матрицы
output.append('')  # Пустая строка
output.append('const Matrix *chars_bitmap[128] = {')
for code in range(128):
    symbol = chr(code)
    if symbol in chars_bitmaps:
        output.append("  /* {:02x} */ &matrix_{:02x},  // '{}'".format(code,
                                                                       code,
                                                                       symbol))
    else:
        output.append("  /* {:02x} */ (void *) 0,".format(code))
output.append('};')

output.append('')  # Пустая строка

output_content = '\n'.join(output)
# print('\n'.join(output))
with open(OUTPUT_FILENAME, 'w') as fp:
    fp.write(output_content)
