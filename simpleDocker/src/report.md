# Simple Docker

## Part 1. Готовый докер

- Выкачиваем докер-образ nginx - "docker pull nginx"
<img src="./img/part1/1.1.png" alt="1.1" /> <br>

- Проверяем наличие докер образа - "docker images | grep nginx"
<img src="./img/part1/1.2.png" alt="1.2" /> <br>

- Запустим образ при помощи "docker run -d nginx", затем проверим, что образ запустился - "docker ps"
<img src="./img/part1/1.3.png" alt="1.3" /> <br>

- Посмотрим информацию о контейнере - "docker inspect \$(docker ps | grep nginx | awk '{print $1}')"
<img src="./img/part1/1.4.png" alt="1.4" /> <br>

- Параметры:
 -- размер контейнера - 67108864
 -- список портов - 80/tcp
 -- IP - 172.17.0.2

- Остановим образ - "docker stop \$(docker ps | grep nginx | awk '{print $1}')"
<img src="./img/part1/1.5.png" alt="1.5" /> <br>

- Запустим докер с портами 80 и 443 - "docker run -d -p 80:80 -p 443:443 nginx".
<img src="./img/part1/1.6.png" alt="1.6" /> <br>

- Убедимся, что по local:80 открывается nginx - "curl localhost:80"
<img src="./img/part1/1.7.png" alt="1.7" /> <br>

- Перезапустим контейнер при помощи "docker restart \$(docker ps | grep nginx | awk '{print $1}')". Убедимся, что он заработал - "docker ps".
<img src="./img/part1/1.8.png" alt="1.8" /> <br>

## Part 2. Операции с контейнером

- Прочитаем конфигурационный файл - "docker exec nginx.conf"
<img src="./img/part2/2.1.png" alt="2.1" /> <br>

- Создаем файл nginx.conf - "mkdir part2 && touch part2/nginx.conf"
<img src="./img/part2/2.2.png" alt="2.2" /> <br>

- Настраиваем в нем по пути /status отдачу страницы статуса nginx
<img src="./img/part2/2.3.png" alt="2.3" /> <br>

- копируем файл nginx.conf в образ докера - "docker cp part2/nginx.conf \$(docker ps | grep nginx | awk '{print $1}'):etc/nginx"
<img src="./img/part2/2.4.png" alt="2.4" /> <br>

- Перезапускаем контейнер - "docker exec \$(docker ps | grep nginx | awk '{print $1}') nginx -s reload"
<img src="./img/part2/2.5.png" alt="2.5" /> <br>

- Смотрим статус сервера nginx - "curl localhos:80/status"
<img src="./img/part2/2.6.png" alt="2.6" /> <br>

- Экспортируем контейнер в архив - "docker export \$(docker ps | grep nginx | awk '{print \$1}') > container.tar". Останавливаем контейнер - "docker stop \$(docker ps | grep nginx | awk '{print $1}')". Удаляем образ - "docker rmi -f nginx"
<img src="./img/part2/2.7.png" alt="2.7" /> <br>

- Удаляем контейнер 
<img src="./img/part2/2.8.png" alt="2.8" /> <br>

- Импортируем контейнер - "docker import -c 'cmd ["nginx","-g","daemon off;"]' -c 'ENTRYPOINT ["\docker-entrypoint.sh"]' con
tainer.tar nginx". Выводим список образов. Запустим контейнер
<img src="./img/part2/2.9.png" alt="2.9" /> <br>

- Проверяем, что отдается страничка со статусом
<img src="./img/part2/2.10.png" alt="2.10" /> <br>

## Part3. Мини веб-сервер


- Создаем файл server.c, пишем в нем "Hello_world"
- Копируем файл в контейнер - "docker cp server.c con:home"
<img src="./img/part3/3.1.png" alt="3.1" /> <br>

- Меняем файл nginx.conf
<img src="./img/part3/3.2.png" alt="3.2" /> <br>

- Копируем его в контейнер. Заходим в оболочку Bash контейнера, обновляем репозитории, скачиваем необхоимые библиотеки.
<img src="./img/part3/3.3.png" alt="3.3" /> <br>
<img src="./img/part3/3.4.png" alt="3.4" /> <br>

- Компилируем, запускаем сервер, перезагружаем образ
<img src="./img/part3/3.5.png" alt="3.5" /> <br>
<img src="./img/part3/3.6.png" alt="3.6" /> <br>

- Открываем localhost:81
<img src="./img/part3/3.7.png" alt="3.7" /> <br>

## Part 4. Свой докер

- Создаем Dockerfile
<img src="./img/part4/4.1.png" alt="4.1" /> <br>

- Создаем скрипт, выполняющий роль ENTRYPOINT
<img src="./img/part4/4.2.png" alt="4.2" /> <br>

- Собираем образ докера, используя имя и тег - camillec(имя):1.0(тег)
<img src="./img/part4/4.3.png" alt="4.3" /> <br>

- Проверяем наличие докер образа
<img src="./img/part4/4.4.png" alt="4.4" /> <br>

- Запускаем собранный докер образ с маппингом 81 порта на 80 на локальной машине и маппингом папки Nginx внутрь контейнера по адресу /etc/nginx/. Проверяем ответ сервера
<img src="./img/part4/4.5.png" alt="4.5" /> <br>

## Part 5. Dockle.

- Устанавливаем Dockle - `VERSION=$(curl --silent "https://api.github.com/repos/goodwithtech/dockle/releases/latest" | \
 grep '"tag_name":' | \
 sed -E 's/.*"v([^"]+)".*/\1/' \
) && curl -L -o dockle.deb https://github.com/goodwithtech/dockle/releases/download/v${VERSION}/dockle_${VERSION}_Linux-64bit.deb
$ sudo dpkg -i dockle.deb && rm dockle.deb`

- Проверяем докер образ с помощью Dockle
<img src="./img/part5/5.1.png" alt="5.1" /> <br>

- Исправляем Dockerfile, чтобы убрать все ошибки
<img src="./img/part5/5.2.png" alt="5.2" /> <br>

-  Собрал докер образ
<img src="./img/part5/5.3.png" alt="5.3" /> <br>

- Запустил Dockle
<img src="./img/part5/5.4.png" alt="5.4" /> <br>

## Part 6. 

- Копируем из Part все файлы в папку server без изменений. Создаем файл docker-compose.yml и меняем nginx,conf и run.sh
<img src="./img/part6/6.1.png" alt="6.1" /> <br>
<img src="./img/part6/6.2.png" alt="6.2" /> <br>
<img src="./img/part6/6.3.png" alt="6.3" /> <br>

- Соберем проект командой - "docker-compose build"
<img src="./img/part6/6.4.png" alt="6.4" /> <br>

- Запустим проект командой - "docker-compose up"
<img src="./img/part6/6.5.png" alt="6.5" /> <br>

- Проверим, что возвращается страница
<img src="./img/part6/6.6.png" alt="6.6" /> <br>














