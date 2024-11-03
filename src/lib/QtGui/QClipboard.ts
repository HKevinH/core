import { NativeElement } from "../core/Component";
import {
  checkIfNativeElement,
  registerNativeWrapFunction,
} from "../utils/helpers";
import { QObject, QObjectSignals } from "../QtCore/QObject";
import { QPixmap } from "./QPixmap";
import { wrapperCache } from "../core/WrapperCache";
import { QMimeData } from "../QtCore/QMimeData";

/**

> The QClipboard class provides access to the window system clipboard.

* **This class is a JS wrapper around Qt's [QClipboard class](https://doc.qt.io/qt-5/QClipboard.html)**

### Example

```javascript
import {
  QClipboard,
  QClipboardMode,
  QApplication
} from "@vixen-js/core";

const clipboard = QApplication.clipboard();
const text = clipboard.text(QClipboardMode.Clipboard);
```
 */
export class QClipboard extends QObject<QClipboardSignals> {
  constructor(native: NativeElement) {
    if (!checkIfNativeElement(native)) {
      throw new Error(
        "QClipboard cannot be initialised this way. Use QApplication::clipboard()"
      );
    }
    super(native);
  }
  clear(mode = QClipboardMode.Clipboard): void {
    this.native?.clear(mode);
  }

  mimeData(mode = QClipboardMode.Clipboard): QMimeData {
    return new QMimeData(this.native?.mimeData(mode));
  }

  setMimeData(src: QMimeData, mode = QClipboardMode.Clipboard): void {
    this.native?.setMimeData(src.native, mode);
  }

  setText(text: string, mode = QClipboardMode.Clipboard): void {
    this.native?.setText(text, mode);
  }
  text(mode = QClipboardMode.Clipboard): string {
    return this.native?.text(mode);
  }
  setPixmap(pixmap: QPixmap, mode = QClipboardMode.Clipboard): void {
    this.native?.setPixmap(pixmap.native, mode);
  }
  pixmap(mode: QClipboardMode): QPixmap {
    return new QPixmap(this.native?.pixmap(mode));
  }
}
wrapperCache.registerWrapper("QClipboardWrap", QClipboard);

export enum QClipboardMode {
  Clipboard = 0,
  Selection = 1,
  FindBuffer = 2,
}

export interface QClipboardSignals extends QObjectSignals {
  onChange: (mode: QClipboardMode) => void;
  onDataChange: () => void;
  onFindBufferChange: () => void;
  onSelectionChange: () => void;
}

registerNativeWrapFunction("QClipboardWrap", (native: any) => {
  return wrapperCache.get<QClipboard>(QClipboard, native);
});
