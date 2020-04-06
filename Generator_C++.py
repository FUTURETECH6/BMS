# > pip3 install faker
import random as r
import faker
f = faker.Faker()

DB_NAME = "library"
BOOK_NUM = 1000
CARD_NUM = 1000
BORR_NUM = 1000
EARLIEST_DATE = "2010-01-01"
GENERATOR_NULL = "null"

bno = []
for i in range(0, 1 * BOOK_NUM):
    string = ""
    for j in range(0, 8):
        string += str(f.random_digit())
    bno.append(string)

category = ["History", "Magazine", "Textbook", "Autobiography", "Dictionary",
            "Realistic novel", "Horror fiction", "Encyclopedia", "Adventure", "Poem"]

title = []
for i in range(0, 1 * BOOK_NUM):
    title.append(f.street_name())

press = []
for i in range(0, 10):  # Restrict number
    press.append(f.street_suffix())

year = []
for i in range(0, 2000):
    year.append(r.randint(10, 2020))  # Need to convert

author = []
for i in range(0, 100):
    author.append(f.name())

price = []
for i in range(0, 100):
    price.append(str(r.randint(5, 50))+".0")

total_stock = []
for i in range(0, 100):
    total_stock.append(r.randint(0, 100))

cno = []
for i in range(0, 1 * CARD_NUM):
    string = ""
    for j in range(0, 7):
        string += str(f.random_digit())
    cno.append(string)

name = []
for i in range(0, 1 * CARD_NUM):
    name.append(f.name())

department = ["Engineering", "Liberal Arts", "Public Health", "Life Science", "Law", "Sociology", "Seminary", "Commerce", "Education",
              "Communications", "Agriculture", "Management", "Computer Science", "Medicine", "Arts", "Tourism", "Designs", "Literature", "Public Affairs", "Software"]

type = ['Student', 'Teacher']

date = []
for i in range(0, 3000):
    date.append(f.date())

# Generate SQL
# print("use " + DB_NAME + ";")
# print("-- Insert into book")
# print("INSERT INTO book VALUES")
for i in range(0, BOOK_NUM):
    stock = total_stock[r.randint(0, 99)]
    total = total_stock[r.randint(0, 99)]
    while stock > total:  # make sure borrow < return
        stock = total_stock[r.randint(0, 99)]
        total = total_stock[r.randint(0, 99)]
    print("(\""+bno[i]+"\",",
          "\""+category[r.randint(0, 9)]+"\",",
          "\""+title[r.randint(0, 1 * BOOK_NUM - 1)]+"\",",
          "\""+press[r.randint(0, 9)]+"\",",
          str(year[r.randint(0, 1999)])+",",
          "\""+author[r.randint(0, 99)]+"\",",
          str(price[r.randint(0, 99)])+",",
          str(total)+",",
          str(stock)+')', end="")
    # if i == BOOK_NUM - 1:
    print(';')
    # else:
        # print(',')

# print("\n\n-- Insert into card")
# for i in range(0, CARD_NUM):
#     print("(\""+cno[r.randint(0, 1 * CARD_NUM - 1)]+"\",",
#           "\""+name[r.randint(0, 1 * CARD_NUM - 1)]+"\",",
#           "\""+department[r.randint(0, 19)]+"\",",
#           "\""+type[r.randint(0, 1)]+"\")", end="")
#     # if i == CARD_NUM - 1:
#     print(';')
#     # else:
#         # print(',')

# print("\n\n-- Insert into borrow")
# # print("INSERT INTO borrow VALUES")
# for i in range(0, BORR_NUM):
#     t1 = date[r.randint(0, 2999)]
#     t2 = date[r.randint(0, 2999)]
#     while t1 > t2 or t1 < EARLIEST_DATE:  # make sure borrow < return
#         t1 = date[r.randint(0, 2999)]
#         t2 = date[r.randint(0, 2999)]
#     if(r.randint(0, 10) == 0):
#         print("(\""+cno[r.randint(0, 99)]+"\",",
#               "\""+bno[r.randint(0, 99)]+"\",",
#               "\""+t1+"\",",
#               GENERATOR_NULL+")", end="")
#     else:
#         print("(\""+cno[r.randint(0, 99)]+"\",",
#               "\""+bno[r.randint(0, 99)]+"\",",
#               "\""+t1+"\",",
#               "\""+t2+"\")", end="")
#     # if i == BOOK_NUM - 1:
#     print(';')
#     # else:
#         # print(',')


# 1. 书book(书号, 类别, 书名,出版社,出版年份,作者,价格,总藏书量,目前库存量)
# 	各属性的类型如下:
# 	bno 		char(8)
# 	category 	char(10)
# 	title 		varchar(40)
# 	press		varchar(30)
# 	year		int
# 	author		varchar(20)
# 	price		decimal(7,2)
# 	total		int
# 	stock		int

# 2. 借书证card(卡号,姓名,单位,类别)
# 	各属性的类型如下:
# 	cno		char(7)
# 	name	varchar(10)
# 	department	varchar(40)
# 	type		char(1)  (class in ('T','G','U','O'))
# 其中T, G, U, O分别代表教师、研究生、本科生、管理人员

# 3. 借书记录borrow(卡号,借书证号,借期,还期)
# 	各属性的类型如下:
# 	cno		char(7)
# 	bno		char(8)
# 	borrow_date	date
# 	return_date	date

# 　　　　f.name　　　　　　# 生成姓名
# 　　　　f.address()　　 　　# 生成地址
# 　　　　f.country()　　  　　# 生成国家
# 　　　　f.province()　　　　# 生成省份
# 　　　　f.city_suffix()　 　　# 生成市，县
# 　　　　f.district()　　　　   # 生成区
# 　　　　f.street_name()  　  # 生成街道名
# 　　　　f.street_suffix() 　　# 生成街、路
# 　　　　f.random_digit()　　# 生成0~9随机数
# 　　　　f.random_element() # 生成随机字母
# 　　　　f.color_name()　　 # 生成随机颜色名
# 　　　　f.date()　　　　　  # 生成随机日期
