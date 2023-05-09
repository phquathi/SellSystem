#include <gtk/gtk.h>

// 回调函数原型声明
static gboolean on_product_selection_clicked(GtkWidget *widget, GdkEvent *event, gpointer data);
static gboolean on_campus_network_clicked(GtkWidget *widget, GdkEvent *event, gpointer data);
static gboolean on_weather_clicked(GtkWidget *widget, GdkEvent *event, gpointer data);

// 商品结构体
typedef struct {
    const gchar *name;
    const gchar *image_path;
    double price;
} Product;

// 商品展示页面回调函数
static void create_product_display(GtkStack *stack);

// 商品点击回调函数
static void on_product_clicked(GtkFlowBoxChild *child, gpointer data);

static void on_back_button_clicked(GtkWidget *widget, gpointer data);

// 商品示例数据
static Product products[] = {
        {"土豆", R"(E:\Smart_Car\SellSystem\R-C.jpg)", 10.0},
        {"土豆B", R"(E:\Smart_Car\SellSystem\R-C.jpg)", 20.0},
        {"土豆C", R"(E:\Smart_Car\SellSystem\R-C.jpg)", 30.0},
        // 更多商品...
};

static GtkWidget *create_home_page(GtkWidget *window, GtkWidget *stack);


int main(int argc, char *argv[]) {
    GtkWidget *stack;
    GtkWidget *window;
    GtkWidget *main_box;
    // 初始化GTK+
    gtk_init(&argc, &argv);

    // 创建主窗口
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "自动售货机售货系统");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 480);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    // 创建 Stack
    stack = gtk_stack_new();
    gtk_container_add(GTK_CONTAINER(window), stack);


    // 将主页添加到堆栈中
    main_box = create_home_page(window, stack);
    gtk_stack_add_named(GTK_STACK(stack), main_box, "home_page");
    // 连接窗口关闭信号

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 显示窗口和所有控件
    gtk_widget_show_all(window);

    // 运行GTK+主事件循环
    gtk_main();

    return 0;
}

static GtkWidget *create_home_page(GtkWidget *window, GtkWidget *stack) {
    // ...
    GtkWidget *main_box;
    GtkWidget *left_box;
    GtkWidget *right_box;
    GtkWidget *label;
    GtkWidget *product_selection_event_box;
    GtkWidget *campus_network_event_box;
    GtkWidget *weather_event_box;
    GtkWidget *product_selection_label;
    GtkWidget *campus_network_label;
    GtkWidget *weather_label;


    // 创建主盒子并添加到窗口
    main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    //gtk_container_add(GTK_CONTAINER(stack), main_box);

    // 创建左侧盒子
    left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(main_box), left_box, TRUE, TRUE, 0);

    // 创建右侧盒子
    right_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(main_box), right_box, TRUE, TRUE, 0);

    // 创建并添加标题标签
    label = gtk_label_new("欢迎使用智能购物小车！");
    gtk_box_pack_start(GTK_BOX(left_box), label, TRUE, TRUE, 0);

    // 创建商品选购板块
    product_selection_event_box = gtk_event_box_new();
    gtk_box_pack_start(GTK_BOX(right_box), product_selection_event_box, TRUE, TRUE, 0);
    g_signal_connect(product_selection_event_box, "button_press_event", G_CALLBACK(on_product_selection_clicked), stack);
    product_selection_label = gtk_label_new("商品选购");
    gtk_container_add(GTK_CONTAINER(product_selection_event_box), product_selection_label);

    // 创建校园网板块
    campus_network_event_box = gtk_event_box_new();
    gtk_box_pack_start(GTK_BOX(right_box), campus_network_event_box, TRUE, TRUE, 0);
    g_signal_connect(campus_network_event_box, "button_press_event", G_CALLBACK(on_campus_network_clicked), NULL);
    campus_network_label = gtk_label_new("校园网");
    gtk_container_add(GTK_CONTAINER(campus_network_event_box), campus_network_label);

    // 创建天气板块
    weather_event_box = gtk_event_box_new();
    gtk_box_pack_start(GTK_BOX(right_box), weather_event_box, TRUE, TRUE, 0);
    g_signal_connect(weather_event_box, "button_press_event", G_CALLBACK(on_weather_clicked), NULL);
    weather_label = gtk_label_new("天气");
    gtk_container_add(GTK_CONTAINER(weather_event_box), weather_label);

    // 显示窗口和所有控件
    gtk_widget_show_all(stack);

    // 连接窗口关闭信号
    g_signal_connect(stack, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_stack_add_named(GTK_STACK(stack), main_box, "home_page");
    return main_box;
}

// 商品选购板块回调函数
static gboolean on_product_selection_clicked(GtkWidget *widget, GdkEvent *event, gpointer data) {
    GtkStack *stack = GTK_STACK(data);
    create_product_display(stack);
    gtk_stack_set_visible_child_name(stack, "product_display");
    return TRUE;
}


// 校园网板块回调函数
static gboolean on_campus_network_clicked(GtkWidget *widget, GdkEvent *event, gpointer data) {
// TODO: 跳转至校园网页面
    return TRUE;
}

// 天气板块回调函数
static gboolean on_weather_clicked(GtkWidget *widget, GdkEvent *event, gpointer data) {
    // TODO: 跳转至天气详情页面
    return TRUE;
}

// 商品展示页面回调函数
static void create_product_display(GtkStack *stack) {
    GtkWidget *product_display_box;
    GtkWidget *scrolled_window;
    GtkWidget *flow_box;
    guint n_products = sizeof(products) / sizeof(Product);
    GtkWidget *header_box;
    GtkWidget *header_bar;
    GtkWidget *back_button;

    // 创建商品展示容器
    product_display_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // 创建 header_box
    header_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(product_display_box), header_box, FALSE, FALSE, 0);

    // 创建 header_bar
    header_bar = gtk_header_bar_new();
    gtk_box_pack_start(GTK_BOX(header_box), header_bar, TRUE, TRUE, 0);

    // 创建返回按钮
    back_button = gtk_button_new_with_label("返回");
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_back_button_clicked), stack);
    gtk_header_bar_pack_start(GTK_HEADER_BAR(header_bar), back_button);

    // 创建滚动窗口
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_box_pack_start(GTK_BOX(product_display_box), scrolled_window, TRUE, TRUE, 0);

    // 创建流布局容器
    flow_box = gtk_flow_box_new();
    gtk_container_add(GTK_CONTAINER(scrolled_window), flow_box);
    gtk_flow_box_set_min_children_per_line(GTK_FLOW_BOX(flow_box), 3);
    gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(flow_box), 3);
    gtk_flow_box_set_selection_mode(GTK_FLOW_BOX(flow_box), GTK_SELECTION_SINGLE);

    // 添加商品到流布局容器
    for (guint i = 0; i < n_products; i++) {
        GtkWidget *product_box;
        GtkWidget *image;
        GtkWidget *label;
        gchar *price_str;

        product_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        image = gtk_image_new_from_file(products[i].image_path);
        gtk_box_pack_start(GTK_BOX(product_box), image, FALSE, FALSE, 0);

        label = gtk_label_new(products[i].name);
        gtk_box_pack_start(GTK_BOX(product_box), label, FALSE, FALSE, 0);

        price_str = g_strdup_printf("%.2f 元", products[i].price);
        label = gtk_label_new(price_str);
        gtk_box_pack_start(GTK_BOX(product_box), label, FALSE, FALSE, 0);
        g_free(price_str);
        gtk_widget_set_size_request(product_box, 200, 200);
        gtk_widget_set_valign(product_box, GTK_ALIGN_START);
        gtk_widget_set_halign(product_box, GTK_ALIGN_CENTER);

        GtkFlowBoxChild *child = GTK_FLOW_BOX_CHILD(gtk_flow_box_child_new());
        gtk_container_add(GTK_CONTAINER(child), product_box);
        gtk_flow_box_insert(GTK_FLOW_BOX(flow_box), GTK_WIDGET(child), -1);
    }

    // 连接商品点击事件
    g_signal_connect(flow_box, "child-activated",G_CALLBACK(on_product_clicked), NULL);
    // 显示窗口和所有控件
    gtk_widget_show_all(product_display_box);

    // 将商品展示页面添加到 stack 中
    gtk_stack_add_named(stack, product_display_box, "product_display");
}

static void on_back_button_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *stack = (GtkWidget *)data;
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "home_page");
}


// 商品点击回调函数
static void on_product_clicked(GtkFlowBoxChild *child, gpointer data) {
    gint index = gtk_flow_box_child_get_index(child);
    Product *selected_product = &products[index];
    // 在这里添加处理商品点击的逻辑，例如显示商品详情或添加到购物车
    g_print("选中的商品: %s\n", selected_product->name);
}
