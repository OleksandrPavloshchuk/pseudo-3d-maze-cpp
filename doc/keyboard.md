Так, ти мислиш у правильному напрямку. Але я б трохи розділив дві речі: **подію натискання клавіші** та **стан клавіатури**.

`KEY_DOWN` і `KEY_UP` — це події, які повідомляють про зміну стану. А рух гравця має залежати від того, які клавіші зараз утримуються.

Наприклад, можна завести в `FpvRenderer` набір прапорців:

```
class FpvRenderer : public Renderer {
private:
    bool moveForward_ = false;
    bool moveBackward_ = false;
    bool rotateLeft_ = false;
    bool rotateRight_ = false;

protected:
    void handleKeyDown(SDL_Keycode key) override;
    void handleKeyUp(SDL_Keycode key) override;
    void updatePlayer();
};
```

У `handleKeyDown`:

```
void FpvRenderer::handleKeyDown(SDL_Keycode key) {
    switch (key) {
        case SDLK_W:
            moveForward_ = true;
            break;
        case SDLK_S:
            moveBackward_ = true;
            break;
        case SDLK_A:
            rotateLeft_ = true;
            break;
        case SDLK_D:
            rotateRight_ = true;
            break;
    }
}
```

А в `handleKeyUp` — відповідно вимикати прапорці.

Тоді в ігровому циклі:

```
while (running) {
    processEvents();
    updatePlayer();
    updateFrameBuffer();
    render();
}
```

А `updatePlayer()` уже дивиться на поточні прапорці й вирішує, що робити.

**Чому не один enum?**

Тому що гравець може одночасно натиснути, наприклад, вперед і повернути ліворуч. Один enum змусив би обирати лише один режим, тоді як незалежні прапорці дозволяють комбінувати дії.

Є ще один важливий нюанс: `KEY_DOWN` може надходити повторно через автоповтор клавіатури. Для перемикання прапорців це не страшно, але варто враховувати `event.key.repeat`, якщо захочеш обробляти саме одноразові натискання.

І ще: швидкість руху краще прив'язати до часу між кадрами (`deltaTime`), а не до кількості проходів циклу. Інакше швидкість гравця залежатиме від FPS.

Отже, я б почав саме з чотирьох `bool` у `FpvRenderer`. Це простіше за enum станів і добре відповідає твоїй моделі керування. А базовий `Renderer` нехай лише передає події через віртуальні методи — він не повинен знати, що таке рух чи поворот гравця.
