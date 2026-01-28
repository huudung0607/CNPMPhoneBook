FROM gcc:latest
WORKDIR /app
COPY Source.cpp .
RUN touch UserList.txt ContactList.txt
RUN g++ -o phonebook_app Source.cpp
CMD ["./phonebook_app"]
