# SDL 2D Game Engine : Ham-Man

## 기본 정보
개발 기간 : 2021.8.7 ~ 2022.1.12

라이브러리 : SDL2-2.0.14

사용 언어 : C++14

개발 환경 : Visual Studio 2019

개발 인원 : 1

개발 목적 : 자체 개발 엔진을 사용한 팩맨 제작

참고 도서 : Game Programming in C++

## 기능
- **SpriteSheetLibrary** : 스프라이트 시트를 불러오고, 지정한 픽셀 크기로 잘라서 저장한다.
- **AnimSpriteSheetComponent** : 스프라이트 시트를 사용한 애니메이션을 실행한다.
- **TileMapComponent** : 타일 종류의 데이터를 가지고 있는 csv파일로부터 타일을 생성한 후, 타일맵을 그린다.
- **Graph** : csv파일로부터 노드와 그래프를 생성한다.
- **PacmanMoveComponent** : 그래프의 노드를 따라 캐릭터를 이동시킨다.
- **PacmanInputComponent** : 플레이어의 입력을 받아 PacmamMoveComponent를 조작한다.
- **GhostAI** : 고스트의 Patrol, Death, Chase 상태에 따라 동작한다.
- **CollisionComponet** : Circle, Rect로 충돌 판정을 한다.

## Youtube
[![Video Label](http://img.youtube.com/vi/ZBEjrwBO8pM/0.jpg)](https://youtu.be/ZBEjrwBO8pM)

※ 빨간 고스트는 Chase속성이 있습니다. 플레이어가 일정 거리 안에 들어오면 일정 시간 또는 일정 거리 동안 플레이어를 따라갑니다.
