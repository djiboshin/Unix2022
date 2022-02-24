#Реквизиты
Игошин Владимир Дмитриевич, 3 курс, z33434, 2022

#Наименование
UNIX знакомство: useradd, nano, chmod, docker, GIT, CI, C

#Цель
Познакомить студента с основами администрирования программных комплексов в ОС семейства UNIX, продемонстрировать особенности виртуализации и контейнеризации, продемонстрировать преимущества использования систем контроля версий (на примере GIT)

#Задача
1. [ОС] Работа в ОС, использование файловой системы, прав доступа, исполение файлов

1.1. В папке /USR/LOCAL/ создать 2 директории: folder_max, folder_min

1.2. Создать 2-х группы пользователей: group_max, group_min

1.3. Создать 2-х пользователей: user_max_1, user_min_1

1.4. Для пользователей из группы *_max дать полный доступ на директории *_max и *_min. Для пользователей группы *_min дать полный доступ только на директорию *_min

1.5. Создать и исполнить (пользователем из той же категории) скрипт в директории folder_max, который пишет текущую дату/время в файл output.log в текущей директории

1.6. Создать и исполнить (пользователем из той же категории) скрипт в директории folder_max, который пишет текущую дату/время в файл output.log в директории *_min

1.7. Исполнить (пользователем *_min) скрипт в директории folder_max, который пишет текущую дату/время в файл output.log в директории *_min

1.8. Создать и исполнить (пользователем из той же категории) скрипт в директории folder_min, который пишет текущую дату/время в файл output.log в директории *_max

1.9. Вывести перечень прав доступа у папок *_min/ *_max, а также у всего содержимого внутри

2. [КОНТЕЙНЕР] docker build / run / ps / images

2.1. Создать скрипт, который пишет текущую дату/время в файл output.log в текущей директории

2.2. Собрать образ со скриптами выше и с пакетом nano (docker build)

2.3. Запустить образ (docker run)

2.4. Выполнить скрипт, который подложили при сборке образа

2.5. Вывести список пользователей в собранном образе

3. [GIT] GitHub / GitLab, в котором будут содержаться все выполненные ЛР

3.1. Создать репозиторий в GitHub или GitLab

3.2. Создать структуру репозитория:

3.2.1. lab_01

3.2.1.1. build

3.2.1.2. src

3.2.1.3. doc

3.2.1.4. cmake (для ЛР 1 опционально)

3.2.2. lab_02

3.2.2.1. ... идентично lab_01 …

3.3. Создать ветки dev / stg / prd, удалить ранее существующие ветки удаленно и локально

3.4. Создать скрипт автоматического переноса ревизий из ветки dev в ветку stg с установкой метки времени (tag). Скрипт в корень репозитория

3.5. Создать скрипт автоматического переноса ревизий из ветки stg в ветку prd с установкой метки времени (tag). Скрипт в корень репозитория

4. [SAVE] Всё, что было сделано в шагах 1-3, сохранить в репозиторий (+ отчет по данной ЛР в папку doc). Фиксацию ревизий производить строго через ветку dev. С помощью скриптов накатить ревизии на stg и на prd.

#Решение
### 1. [ОС] Работа в ОС, использование файловой системы, прав доступа, исполение файлов

1. В папке /USR/LOCAL/ создать 2 директории: folder_max, folder_min
   ```commandline
   cd /usr/local
   sudo mkdir folder_max
   sudo mkdir folder_min
   ```
2. Создать 2-х группы пользователей: group_max, group_min
   ```commandline
   sudo groupadd group_max
   sudo groupadd group_min
   ```
3. Создать 2-х пользователей: user_max, user_min
   ```commandline
   sudo useradd -g group_max user_max
   sudo passwd user_max
   sudo useradd -g group_min user_min
   sudo passwd user_min
   ```
4. Для пользователей из группы *_max дать полный доступ на директории *_max и *_min. Для пользователей группы *_min дать полный доступ только на директорию *_min
   ```commandline
   sudo chgrp group_max folder_max
   sudo chmod g+xwr folder_max
   sudo usermod -a -G group_min user_max
   sudo chgrp group_min folder_min
   sudo chmod g+xwr folder_min
   ```
5. Создать и исполнить (пользователем из той же категории) скрипт в директории folder_max, который пишет текущую дату/время в файл output.log в текущей директории
   ```commandline
   cd folder_max
   su user_max
   nano scr.sh
   ```
   ```shell
   echo $(date) >> output.log
   ```
   ```commandline
   bash scr.sh
   ```
6. Создать и исполнить (пользователем из той же категории) скрипт в директории folder_max, который пишет текущую дату/время в файл output.log в директории *_min
   ```commandline
   nano scr_max.sh
   ```
   ```shell
   echo $(date) >> /usr/local/folder_min/output.log
   ```
   ```commandline
   bash scr_max.sh
   ```
7. Исполнить (пользователем *_min) скрипт в директории folder_max, который пишет текущую дату/время в файл output.log в директории *_min
   ```commandline
   su user_min -c "bash scr_max.sh"
   ```
   ```commandline
   scr_max.sh: line 1: /usr/local/folder_min/output.log: Permission denied
   ```
   Файл output.log принадлежит user_max, поэтому сначала поменяем права
   ```commandline
   cd ../folder_min
   sudo chmod o+w output.log
   su user_min -c "bash /usr/local/folder_max/scr_max.sh"
   ```
8. Создать и исполнить (пользователем из той же категории) скрипт в директории folder_min, который пишет текущую дату/время в файл output.log в директории *_max
   ```commandline
   nano scr_max.sh
   ```
   ```shell
   echo $(date) >> /usr/local/folder_max/output.log
   ```
   Поменяем права на `folder_max/output.log` и выполним
   ```commandline
   sudo chmod o+w ../folder_max/output.log
   su user_min -c "bash scr_max.sh"
   ```
9. Вывести перечень прав доступа у папок *_min/ *_max, а также у всего содержимого внутри
   ```commandline
   ls -l | grep "folder"
   ```
   Результат:
   ```commandline
   drwxrwxr-x 1 root group_max 512 Feb 20 18:36 folder_max
   drwxrwxr-x 1 root group_min 512 Feb 20 18:50 folder_min
   ```
   ```commandline
   ls -l folder_max folder_min
   ```
   Результат:
   ```commandline
   folder_max:
   total 0
   -rw-r--rw- 1 user_max group_max 58 Feb 20 19:03 output.log
   -rw-r--r-- 1 user_max group_max 27 Feb 20 18:36 scr.sh
   -rw-r--r-- 1 user_max group_max 49 Feb 20 17:44 scr_max.sh
    
   folder_min:
   total 0
   -rw-r--rw- 1 user_max group_max 87 Feb 20 19:06 output.log
   -rw-r--r-- 1 user_min group_min 49 Feb 20 17:57 scr_max.sh
   ```

##2. [КОНТЕЙНЕР] docker build / run / ps / images
1. Создать скрипт, который пишет текущую дату/время в файл output.log в текущей директории
    ```commandline
    cd /usr/local
    nano echo_date.sh
    ```
   ```shell
    echo $(date) > output.log
   ```
2. Собрать образ со скриптами выше и с пакетом nano (docker build)
    ```commandline
    nano Dockerfile
    ```
    ```dockerfile
    FROM ubuntu:18.04
    WORKDIR /
    COPY folder_max folder_max
    COPY folder_min folder_min
    COPY echo_date.sh .
    
    RUN apt-get update
    RUN apt-get install nano
    ```
    ```commandline
    sudo docker build -t echo .
    ```
    Результат:
    ```commandline
    Successfully built 1f06ffedf73e
    Successfully tagged echo:latest
    ```
3. Запустить образ (docker run)
    ```commandline
    sudo docker run -it echo
    ```
   Результат:
    ```text
    root@02b085f6cbd6:/#
    ```
4. Выполнить скрипт, который подложили при сборке образа
    ```commandline
    bash echo_date.sh
    ```
5. Вывести список пользователей в собранном образе
    ```commandline
    cut -d: -f1 /etc/passwd
    ```
   Результат:
    ```text
    root
    daemon
    bin
    sys
    sync
    games
    man
    lp
    mail
    news
    uucp
    proxy
    www-data
    backup
    list
    irc
    gnats
    nobody
    _apt
    ```
##3. [GIT] GitHub / GitLab, в котором будут содержаться все выполненные ЛР
1. Создать репозиторий в GitHub или GitLab
    Создаем репозиторий на гитхабе, на машине выполняем
    ```commandline
    mkdir Unix2022
    cd Unix2022
    git init
    git commit
    git remote add origin https://github.com/djiboshin/Unix2022.git
    git branch -M dev
    git push -u origin dev
    ```
    Чтобы сохранить логин и пароль
    ```commandline
    git config --global credential.helper store
    git pull
    ```
    Результат: запушена ветка dev. 
2. Создать структуру репозитория
    Создам скрипт `new_lab_folders.sh`, который создает папки `lab_x`, `build`, `src`, `doc` и `cmake` под новую лабу под номером `x`. В каждой папке создается файл `.gitkeep`
    ```shell
    #!/bin/bash
    if [ -n "$1" ]; then
            if ! [[ "$1" =~ ^[0-9]+$ ]]; then
                    echo "int only"
                    exit 1
            else
                    dir_name=$(printf "lab_%02d" $1)
                    mkdir -p "$dir_name/build" && touch "$_/.gitkeep"
                    mkdir -p "$dir_name/src" && touch "$_/.gitkeep"
                    mkdir -p "$dir_name/doc" && touch "$_/.gitkeep"
                    mkdir -p "$dir_name/cmake" && touch "$_/.gitkeep"
                    exit 0
            fi
    else
            echo "1 int arg required"
    fi
    ```
    После использования скрипта: добавить папки в индексацию.
    ```commandline
    git add -A
    ```
3. Создать ветки dev / stg / prd, удалить ранее существующие ветки удаленно и локальн
    ```commandline
    git checkout -b stg
    git push origin stg
    ```
    Результат:
    ```commandline
    Switched to a new branch 'stg'
    Total 0 (delta 0), reused 0 (delta 0)
    remote:
    remote: Create a pull request for 'stg' on GitHub by visiting:
    remote:      https://github.com/djiboshin/Unix2022/pull/new/stg
    remote:
    To https://github.com/djiboshin/Unix2022.git
     * [new branch]      stg -> stg
    ```
    Аналогично с `prd`

    Чтобы удалить ветку:
    ```commandline
    git branch -d <branchname>
    git push -d origin <branchname>
    ```
4. Создать скрипт автоматического переноса ревизий из ветки dev в ветку stg с установкой метки времени (tag). Скрипт в корень репозитория
    ```commandline
    #!/bin/bash
    git push origin dev
    git checkout stg
    git reset --hard
    git pull origin stg
    git merge dev
    git tag `date "+%d-%b-%Y-%H%M%S"`
    git push origin stg
    git checkout dev
    ```
5. Создать скрипт автоматического переноса ревизий из ветки stg в ветку prd с установкой метки времени (tag). Скрипт в корень репозитория
    ```commandline
    #!/bin/bash
    git checkout prd
    git reset --hard
    git pull origin prd
    git merge stg
    git tag `date "+%d-%b-%Y-%H%M%S"`
    git push origin prd
    git checkout dev
    ```
##4. [SAVE] Всё, что было сделано в шагах 1-3, сохранить в репозиторий (+ отчет по данной ЛР в папку doc). Фиксацию ревизий производить строго через ветку dev. С помощью скриптов накатить ревизии на stg и на prd.

#Заключение
В данной лабораторной работе я узнал о правах доступа, научился создавать докер-образы. Разобрался в системе управления версиями git, разобрался с написанием простейших скриптов. Было интересно.