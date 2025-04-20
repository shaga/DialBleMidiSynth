# DialBleMidiSynth

## using device

* [M5Dial](https://docs.m5stack.com/ja/core/M5Dial)
    * [USB Cパネルマウントアダプタ](https://amzn.to/4lLOPcv)
    * [タカチ製埋込み型電池ボックス単4x4](https://www.sengoku.co.jp/mod/sgk_cart/detail.php?code=EEHD-65KG)
        [ロッカスイッチ](https://www.sengoku.co.jp/mod/sgk_cart/detail.php?code=EEHD-4SZH)
* [Unit Synth](https://docs.m5stack.com/ja/unit/Unit-Synth)
    * [2W/8Ω スピーカー](https://eleshop.jp/shop/g/gG9H12C/)

## hardware

1. [レーザーカット用のデータ](hardware/case/lasercut.pdf)を使って、3mm厚のMDFをカットして、ケースの各面を作成。
2. 電池ボックの赤リード線をロッカスイッチに接続し、別の赤リード線を別の端子に接続し、M5Dialの電源用コネクタに電池ボックスの黒リード線ともに接続する。
3. Unit Synthを分解し、基板のスピーカーコネクタを外し、用意したスピーカーを接続する
    * コネクタはMolex PicoBlade
4. スピーカー、電池ボックス、M5Dial、USB Cパネルマウントアダプタ、ロッカスイッチをケースに固定
    * スピーカーは前面
    * 電池ボックスは底面
    * M5Dialは上面
    * USB Cパネルマウントアダプタとロッカスイッチは背面
5. ケースの上面以外を組み立てて、ボンドで固定
6. ケーブルを接続する
    * Unit SynthからGroveケーブル
    * USB CパネルマウントアダプタからType-Cケーブル(一方がL字型がよいかも)
7. ケーブルをM5Dialに接続
    * GroveコネクタはPortA(赤)に接続
8. 上面を固定する