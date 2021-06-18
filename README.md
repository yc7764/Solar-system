# Solar-system
OpenGL을 이용하여 태양계의 행성들을 그래픽으로 구현한 프로그램  
글로 표현되어 있는 정보보다 사실감있게 입체적으로 묘사하여 눈으로 확인하여 더 빠른 이해를 돕기 위해 제작  
태양계의 행성들이 자전하고 공전하는 모습을 볼 수 있으며, 각 행성들의 간략한 정보를 확인할 수 있다.  

![캡처](https://user-images.githubusercontent.com/59434021/122498272-c60e6200-d029-11eb-9fdd-c92f374e649b.jpg)
![캡처3](https://user-images.githubusercontent.com/59434021/122498302-d7576e80-d029-11eb-8f46-e8d614e8dbe7.jpg)
  
## 상세 설명
- Texture mapping - 2차원 이미지를 3차원 구 표면에 렌더링하여 사실감 있는 입체 화상을 구현
- Sky box - 태양계가 있는 우주 공간을 표현하기 위하여 sky box로 배경을 표현
- Picking selection mode - 클릭 이벤트 발생 시 마우스의 위치 좌표를 구하여 선택된 행성을 구별하고 그 행성의 정보를 사용자에게 출력
- Message box - 행성의 자전과 공전의 주기, 지름 등 상세 정보를 사용자에게 메시지 박스로 출력
