## Styling
These are the Styles used throughout the project.
#### QWidget
```
background-color: rgb(0, 0, 0);
```
#### QTabWidget
```
background-color: rgb(0, 0, 0);
color: rgb(115, 210, 22);
font-size: 24px;

QTabWidget::pane {
	border: 2ṕx solid #424242;
}

QTabBar::tab {
	border: 2px solid #424242;
}

QTabBar::tab:selected {
	background: #141414;
}
```

#### QCheckBox
```
QCheckBox {
    color: rgb(115, 210, 22);
    background: none;
    font: 24px;
}

QCheckBox::indicator {
    width: 24px;
    height: 24px;
}
```

#### QSlider
```
QSlider::add-page:horizontal {
    background: #22b52a;
    border: 2px solid #424242;
    height: 10px;
    border-radius: 4px;
}

QSlider::handle:horizontal {
    background: #22b52a;
    border: 2px solid #424242;
    width: 12px;
    margin-top: -2px;
    margin-bottom: -2px;
    border-radius: 4px;
}
```