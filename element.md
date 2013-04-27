---
layout: layout
title: Element/Brain/Movement Class
---
# (Element/Brain/Movement) Class
---

ここではElementBaseクラス及び、
そのサブクラスであるBrainBaseとMovementBaseの機能と役割について説明します。

---
## Class Diagram

継承関係などのクラス図は以下のようになっています：  

![クラス図](images/130427_element.pdf "Elementクラス図")



---

## ElementBase

---

## BrainBase

BrainクラスはElementBaseを継承するクラスで、
メンバ変数としてElementBaseへのポインタの配列であるelementListを持ちます。
これがBrainの木構造において、自分が持つ枝を表現しており、
枝には任意のBrain/Movementを格納することができます。

---

## MovementBase

---
