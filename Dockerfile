FROM madmanfred/qt-webassembly:qt5.15-em1.39.7 AS frontend-builder

#RUN apk update && apk add git
#RUN git clone --recursive https://github.com/Zebreus/pruefungsplaner.git /pruefungsplaner-frontend
COPY . /pruefungsplaner-frontend
RUN mkdir -p /install && cd /pruefungsplaner-frontend/ && qmake && make -j4 install INSTALL_ROOT=/install/

FROM nginx:alpine
MAINTAINER Lennart E.
COPY --from=frontend-builder /install/ /usr/share/nginx/html
