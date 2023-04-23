# Navify 
## The Intellegent Navigational System

capable of guiding user you their destination in a simple user-friendly manner

**built using**  `c++` , `react`, `opencv`, `firebase`, `sfml`


![Navify][internal-source]

[internal-source]: /resources/navify_web_app.png 'Navify'
<img width="1362" alt="before1" src="resources/before1.png">
<img width="1362" alt="after1" src="resources/after1.png">

Demo Trailer: 
<https://youtu.be/ss9jFM32Tdg> 

## Supported Features

Format | Supported
------------ | -------------
.png| YES
.jpeg | YES
.jpg | YES
iphone | YES
 android| YES
paper | YES
toilet paper | YES
Handwritten | YES
Computer Generated| YES



## Intructions to `USE` program on `any image` (C++)
- clone repository into desired dir
```
git clone https://github.com/AotChn/Navify.git
```
- build project in visual code or IDE

- place desired map image into same dir
- create a `Navify` object and set threshold
```C++
Navify v;
Navify::graph::set_threshold(150);
```
- import image
```C++
   v.import_image("image_name");
```
- set start and end coords 
```C++
   v.set_start(node{0,0});
   v.set_end(node{1100, 600});
```
- finally we are all set to `run` the program! 
## Call in `Main()`

```C++
int main() {

   Navify v;
   Navify::graph::set_threshold(150);

   v.import_image("image_name");
   v.set_start(node{0,0});
   v.set_end(node{1100, 600});

   run();
   v.display();

   return 0;
}
```

## Bugs/issues
- Certain cases gives suppar paths
- Unconnected frontend and backend
- C++ -> firebase conflict

## What To Expect Next 
- Full workable web-app
- mobile deployment
- more robust maps
- Increased amount of preset maps 
- Hearing Acessiblities

</br></br>


```
Contributors:

   Aot Chanthorn
   ChungYin Lee
   Dennis Gavrilenko
   Mahir Anand

```
