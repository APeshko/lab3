#include <iostream>
#include <memory>

class Observer;

class Subject {
    std::weak_ptr<Observer> weak_observer; //weak_ptr используется для наблюдения за объектом Observer, не увеличивая счётчик ссылок
// ссылка на наблюдателя
public:
  // Установка наблюдателя
    void setObserver(std::shared_ptr<Observer> obs) { 
        weak_observer = obs; // сохраняем weak_ptr (не увеличивает счётчик ссылок)
    }
    // метод для уведомления наблюдателя
    void notify();
};

class Observer : public std::enable_shared_from_this<Observer> { 
//enable_shared_from_this позволяет безопасно получить shared_ptr из метода класса
public:
// Подписка на субъект
    void subscribe(Subject& subj) {
        // Получаем shared_ptr из this (наследование enable_shared_from_this)
        subj.setObserver(shared_from_this());
    }
    // Реакция на уведомление
    void onNotify() {
        std::cout << "Получено уведомление!" << std::endl;
    }
};

void Subject::notify() {
    if (auto obs = weak_observer.lock()) { // метод lock() преобразует weak_ptr в shared_ptr для безопасного доступа
        obs->onNotify();
    } else {
        std::cout << "наблюдателя больше нет" << std::endl; //проверка есть ли наблюдатель перед уведомлением его
    }
}
//lock() пытается создать shared_ptr из weak_ptr
//если исходный объект ещё существует - возвращает валидный shared_ptr
//если объект уже удалён - возвращает nullptr

int main() {
    auto subject = Subject();
    {
        auto observer = std::make_shared<Observer>(); // наблюдатель создаётся через shared_ptr, что демонстрирует разделяемое владение
        observer->subscribe(subject);
        subject.notify(); // Работает
    } // здесь, weak_ptr не продлевает жизнь объекта — после удаления observer уведомление не срабатывает
    subject.notify(); // Не работает - наблюдатель удалён
    
   //Subject (субъект) уведомляет Observer (наблюдателя)
//наблюдатель м/б удалён, и субъект это корректно обрабатывает
}
