# UEBuffSystem

Simple system of Buffs (effects that affect game entities). The system allows you to build complex chains of buffs and projectiles based on the parameters of effects and carriers. For information on how to use this system, see the "how to use" section.

![Demo preview](media/00_demo_preview.png)


# Content

1. [Technical task](#technical-task)
1. [Idea](#idea)
1. [Implementation](#implementation)
    * [Step 1: Demo characters](#step-1-demo-characters)
    * [Step 2: Base classe](#step-2-base-classes)
    * [Step 3: Parameters and parameter chains](#step-3-parameters-and-parameter-chains)
1. [How to use]()

# Technical task

The original text of the technical task:

```
Тестовое задание (ориентировочный эстимейт 3 часа)

Реализовать систему Баффов (эффекты, влияющие на игровые сущности). Реализовать именно новую систему, а не использовать Gameplay Ability System.

На сцене присутствует персонаж игрока и другие персонажи. У них есть параметры - Жизни, Скорость перемещения. Неигровые персонажи перемещаются линейно в случайном направлении по сцене с заданной скоростью перемещения.
Персонаж игрока имеет 3 оружия. Стрельба из них происходит по нажатию кнопок 1, 2, 3. Оружие выстреливает пулей и при коллизии воздействует на всех в определенном радиусе. 
Каждое оружие накладывает определенный бафф на цели в радиусе - Мгновенное снижение жизней, Снижение жизней за определенный промежуток времени, снижение скорости перемещения на определенное время. Параметры Баффов настраиваются из таблицы DataTable.
При достижении 0 жизней персонаж умирает.
Пока бафф висит на персонаже, опционально: на нем проигрывается соответствующий эффект.

Опционально: индикация повреждений/оставшегося здоровья с помощью виджета над персонажами. Текущие Баффы персонажей. Достаточно текстовой информации

Важна реализация и структура классов, ресурсы для отображения эффектов из любых источников. Визуальная составляющая не имеет значения, главное соответствие ТЗ.

```

# Idea

# Implementation

I think the best way to start the task is with the architecture of the future application. To do this, we will separate part of the implementation of the Buff System itself and the game code. Let's create a `UEBuffSystem` plugin, in which we will implement a set of classes and data, and the code of the game itself will store the implementation of connecting this plugin to the game in order to demonstrate its performance. Accordingly, we distinguish two main modules:
* `UEBuffSystemDemo` - the main module of the game (demo application)
* `UEBuffSystem` - a module wrapped in a plug-in, which can later be reused in other projects.


## Step 1: Demo characters

In the main game module, let's create a simple enemy class. We will use it to test and demonstrate buff effects. The model will be used as a standard manikin. We will create the following characteristics for the character class:

* base movement speed;
* scale character;
* character's health;
* character color.

This is enough to demonstrate.

## Step 2: Base classes

For simplicity and speed of implementation, let's create base classes that will be implemented as Actors. Let the base class hierarchy look something like this:

```
* BuffDebuffCarrierBase (AActor)

* BuffDebuffEffectBase (AActor)
```

`BuffDebuffCarrierBase` - an entity in the world that will carry the buff or debuff effect. It can be a pickup in the world, or as indicated in the task, it can be a projectile bullet.

`BuffDebuffEffectBase` - an abstract entity, in the life cycle of which the impact on characteristics will be carried out. When the "death" of the object - the effect will be removed.

## Step 3: Parameters and parameter chains 

# How to use