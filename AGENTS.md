 このリポジトリはWindows CE 1から、CE6までの資料を集積するリポジトリである。
収集先の対象サイトは、microsoft公式サイト、wayback,msdn,mslearn,msdocである。
収集方法は github actionsを使用する。
github actionsを走らせこれから作成するharvest.pyを実行し、このリポジトリへ収集データを集める。
収集ページは、ほとんど統一された形式だが一部サイトで不特定の特殊構造となるためできるだけ生のデータで収集する。
urlも、管理しやすい形式となっている。
収集したデータの保存構造は
MSLearn/
MSDN/
Microsoft/
など、収集したurlの種類ごとにトップは分け、その配下についてはurl?の階層？ごとに分ける。

収集先のurlについてだが、1ファイルに収集するurl？