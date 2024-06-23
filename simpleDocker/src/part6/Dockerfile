FROM nginx

WORKDIR /home/

COPY ./nginx.conf /etc/nginx/nginx.conf
COPY ./run.sh .

RUN apt-get update && apt-get install -y gcc spawn-fcgi libfcgi-dev; \
    chown -R nginx:nginx /etc/nginx/nginx.conf; \
    chown -R nginx:nginx /var/cache/nginx; \
    chown -R nginx:nginx /home; \
    touch /var/run/nginx.pid; \
    chown -R nginx:nginx /var/run/nginx.pid; \
    chmod u-s /usr/bin/*; \
    chmod g-s /usr/bin/*; \
    chmod g-s /usr/sbin/*; \
    rm -rf /var/lib/apt/lists

HEALTHCHECK --interval=5m --timeout=3s \
    CMD curl --fail http://localhost || exit 1
USER nginx

ENTRYPOINT ["sh", "run.sh"]
 