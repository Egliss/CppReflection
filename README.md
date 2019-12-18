# CppReflection
## これは何？
VisualStudioの拡張機能を利用してVisualC++で静的/動的なリフレクションを実現するためのサンプルコードです。

## 動作環境

### 共通
+ Windows10
+ VisualStudio2019
  + VisualStudio for Macでは動作しません。
### ランタイム
+ C++17

### 拡張機能
+ C# 7.x

## ざっくり解説
VisualStudioSDKにはC++リフレクション結果を取得するAPIがあるのでそれをうまく使ってC++の世界にリフレクションをもたらします。

ランタイムはUnityのGameObject/Componentを雑に実装しており、GetComponent\<T\>やAddComponent(const std::string& typeName)等にリフレクションを使用しています。

CppReflectionプロジェクトを実行して立ち上がってきたVisualStudioのツールタブからCppReflectionを選択することでC++コードを生成します。

拡張機能から生成されるソースは`StaticType.hpp`と`DynamicType.cpp`の２つです。