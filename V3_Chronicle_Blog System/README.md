
# 📝 v3: Chronicle (Blog System)

[![Version](https://img.shields.io/badge/Version-3.0-blue.svg)](https://github.com/apdalah/Cpp-Evolution-Lab)
[![Status](https://img.shields.io/badge/Status-Planned-lightgrey.svg)](https://github.com/apdalah/Cpp-Evolution-Lab)
[![Paradigm](https://img.shields.io/badge/Paradigm-OOP_+_Patterns-green.svg)](https://github.com/apdalah/Cpp-Evolution-Lab)

> **The Evolution**: From authentication to full-featured blogging platform

---

## 📌 Version Overview

**Chronicle** transforms the authentication system into a complete blog platform. Building on the OOP foundation from v2, this version introduces content management, user roles, commenting systems, and advanced features that bring the project to life as a real-world application.

### 🎯 Primary Goals

- 📄 Implement comprehensive post management (CRUD operations)
- 💬 Add threaded comment system with moderation
- 👥 Create role-based access control (Admin, Author, Commenter)
- 🏷️ Add content categorization and tagging
- 🔍 Implement full-text search functionality
- 📊 Build content analytics and statistics
- 🔔 Add notification system
- ⭐ Implement likes and reactions

---

## 🏗️ Architecture

### Extended Class Diagram

```
┌──────────────────────────────────────────────────────────────┐
│                        User Class                            │
│                    (inherited from v2)                       │
├──────────────────────────────────────────────────────────────┤
│ + role: UserRole (Admin/Author/Commenter)                   │
│ + posts: vector<Post*>                                       │
│ + comments: vector<Comment*>                                 │
│ + followers: vector<User*>                                   │
├──────────────────────────────────────────────────────────────┤
│ + createPost(title, content): Post                           │
│ + deletePost(postId): void                                   │
│ + addComment(post, content): Comment                         │
│ + followUser(user): void                                     │
│ + getPostCount(): int                                        │
└──────────────────────────────────────────────────────────────┘
                            │
                            ▼
┌──────────────────────────────────────────────────────────────┐
│                        Post Class                            │
├──────────────────────────────────────────────────────────────┤
│ - postId: string (UUID)                                      │
│ - author: User*                                              │
│ - title: string                                              │
│ - content: string                                            │
│ - category: Category                                         │
│ - tags: vector<string>                                       │
│ - comments: vector<Comment*>                                 │
│ - likes: vector<User*>                                       │
│ - views: int                                                 │
│ - createdAt: DateTime                                        │
│ - updatedAt: DateTime                                        │
│ - status: PostStatus (Draft/Published/Archived)             │
├──────────────────────────────────────────────────────────────┤
│ + Post(author, title, content)                               │
│ + publish(): void                                            │
│ + archive(): void                                            │
│ + addComment(comment): void                                  │
│ + like(user): void                                           │
│ + unlike(user): void                                         │
│ + incrementViews(): void                                     │
│ + edit(newTitle, newContent): void                           │
│ + addTag(tag): void                                          │
│ + removeTag(tag): void                                       │
│ + getCommentCount(): int                                     │
│ + getLikeCount(): int                                        │
└──────────────────────────────────────────────────────────────┘
                            │
                            ▼
┌──────────────────────────────────────────────────────────────┐
│                      Comment Class                           │
├──────────────────────────────────────────────────────────────┤
│ - commentId: string (UUID)                                   │
│ - author: User*                                              │
│ - post: Post*                                                │
│ - content: string                                            │
│ - parentComment: Comment*  (for threading)                   │
│ - replies: vector<Comment*>                                  │
│ - likes: vector<User*>                                       │
│ - createdAt: DateTime                                        │
│ - isModerated: bool                                          │
├──────────────────────────────────────────────────────────────┤
│ + Comment(author, post, content)                             │
│ + reply(user, content): Comment                              │
│ + like(user): void                                           │
│ + moderate(): void                                           │
│ + edit(newContent): void                                     │
│ + delete(): void                                             │
│ + getReplies(): vector<Comment*>                             │
└──────────────────────────────────────────────────────────────┘
                            │
                            ▼
┌──────────────────────────────────────────────────────────────┐
│                  BlogManager Class                           │
├──────────────────────────────────────────────────────────────┤
│ - posts: map<string, Post*>                                  │
│ - categories: vector<Category>                               │
│ - searchIndex: SearchIndex*                                  │
├──────────────────────────────────────────────────────────────┤
│ + createPost(user, title, content): Post                     │
│ + getPost(postId): Post*                                     │
│ + getAllPosts(): vector<Post*>                               │
│ + getPostsByUser(user): vector<Post*>                        │
│ + getPostsByCategory(category): vector<Post*>                │
│ + getPostsByTag(tag): vector<Post*>                          │
│ + searchPosts(query): vector<Post*>                          │
│ + deletePost(postId): void                                   │
│ + getTrendingPosts(): vector<Post*>                          │
│ + getRecentPosts(count): vector<Post*>                       │
└──────────────────────────────────────────────────────────────┘
                            │
                            ▼
┌──────────────────────────────────────────────────────────────┐
│                 PermissionManager Class                      │
├──────────────────────────────────────────────────────────────┤
│ - rolePermissions: map<UserRole, Permissions>                │
├──────────────────────────────────────────────────────────────┤
│ + canCreatePost(user): bool                                  │
│ + canEditPost(user, post): bool                              │
│ + canDeletePost(user, post): bool                            │
│ + canModerateComments(user): bool                            │
│ + canManageUsers(user): bool                                 │
│ + grantPermission(user, permission): void                    │
└──────────────────────────────────────────────────────────────┘
                            │
                            ▼
┌──────────────────────────────────────────────────────────────┐
│                   SearchEngine Class                         │
├──────────────────────────────────────────────────────────────┤
│ - index: InvertedIndex                                       │
│ - stopWords: set<string>                                     │
├──────────────────────────────────────────────────────────────┤
│ + indexPost(post): void                                      │
│ + search(query): vector<Post*>                               │
│ + searchByTitle(query): vector<Post*>                        │
│ + searchByContent(query): vector<Post*>                      │
│ + searchByAuthor(author): vector<Post*>                      │
│ + rebuildIndex(): void                                       │
└──────────────────────────────────────────────────────────────┘
                            │
                            ▼
┌──────────────────────────────────────────────────────────────┐
│                  NotificationSystem Class                    │
├──────────────────────────────────────────────────────────────┤
│ - notifications: map<User*, vector<Notification>>            │
├──────────────────────────────────────────────────────────────┤
│ + notifyNewComment(post, comment): void                      │
│ + notifyNewFollower(user, follower): void                    │
│ + notifyPostLiked(post, user): void                          │
│ + getNotifications(user): vector<Notification>               │
│ + markAsRead(notification): void                             │
└──────────────────────────────────────────────────────────────┘
```

### System Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                    Presentation Layer                       │
│          (Console UI - upgraded in v4)                      │
├─────────────────────────────────────────────────────────────┤
│  • Post viewing and creation                                │
│  • Comment threading display                                │
│  • User profile management                                  │
│  • Search interface                                         │
└────────────┬────────────────────────────────────────────────┘
             │
┌────────────▼────────────────────────────────────────────────┐
│                   Business Logic Layer                      │
├─────────────────────────────────────────────────────────────┤
│  BlogManager      │  PermissionManager  │  SearchEngine     │
│  User Management  │  Comment System     │  Notifications    │
└────────────┬────────────────────────────────────────────────┘
             │
┌────────────▼────────────────────────────────────────────────┐
│                      Data Access Layer                      │
│                 (File-based - upgraded in v5)               │
├─────────────────────────────────────────────────────────────┤
│  posts.txt    │  comments.txt   │  categories.txt           │
│  users.txt    │  tags.txt       │  notifications.txt        │
└─────────────────────────────────────────────────────────────┘
```

---

## 📁 File Structure

```
v3-chronicle/
│
├── include/
│   ├── core/
│   │   ├── User.h                      # Extended from v2
│   │   ├── Post.h                      # Blog post entity
│   │   ├── Comment.h                   # Comment entity
│   │   ├── Category.h                  # Content categorization
│   │   └── Tag.h                       # Tagging system
│   │
│   ├── managers/
│   │   ├── BlogManager.h               # Post management
│   │   ├── CommentManager.h            # Comment operations
│   │   ├── PermissionManager.h         # Access control
│   │   └── NotificationSystem.h        # User notifications
│   │
│   ├── utils/
│   │   ├── SearchEngine.h              # Full-text search
│   │   ├── Analytics.h                 # Statistics tracking
│   │   └── ContentFilter.h             # Moderation tools
│   │
│   └── enums/
│       ├── UserRole.h                  # Admin/Author/Commenter
│       ├── PostStatus.h                # Draft/Published/Archived
│       └── NotificationType.h          # Event types
│
├── src/
│   ├── core/
│   │   ├── Post.cpp
│   │   ├── Comment.cpp
│   │   ├── Category.cpp
│   │   └── Tag.cpp
│   │
│   ├── managers/
│   │   ├── BlogManager.cpp
│   │   ├── CommentManager.cpp
│   │   ├── PermissionManager.cpp
│   │   └── NotificationSystem.cpp
│   │
│   ├── utils/
│   │   ├── SearchEngine.cpp
│   │   ├── Analytics.cpp
│   │   └── ContentFilter.cpp
│   │
│   └── main.cpp
│
├── data/
│   ├── users.txt                       # From v2
│   ├── posts.txt                       # Post storage
│   ├── comments.txt                    # Comment storage
│   ├── categories.txt                  # Category definitions
│   ├── tags.txt                        # Available tags
│   └── notifications.txt               # User notifications
│
├── tests/
│   ├── PostTests.cpp
│   ├── CommentTests.cpp
│   ├── PermissionTests.cpp
│   ├── SearchTests.cpp
│   └── IntegrationTests.cpp
│
└── README.md
```

---

## ✨ Features

### 1. Complete Post Management 📄

```cpp
class Post {
public:
    // Create new post
    Post(User* author, string title, string content) {
        this->postId = generateUUID();
        this->author = author;
        this->title = title;
        this->content = content;
        this->status = PostStatus::DRAFT;
        this->createdAt = DateTime::now();
        this->views = 0;
    }
    
    // Publish post
    void publish() {
        if (status == PostStatus::DRAFT) {
            status = PostStatus::PUBLISHED;
            updatedAt = DateTime::now();
            notifyFollowers();
        }
    }
    
    // Edit post
    void edit(const string& newTitle, const string& newContent) {
        if (canEdit()) {
            title = newTitle;
            content = newContent;
            updatedAt = DateTime::now();
        }
    }
    
    // Like system
    void like(User* user) {
        if (!isLikedBy(user)) {
            likes.push_back(user);
            NotificationSystem::notifyPostLiked(this, user);
        }
    }
    
    // Analytics
    void incrementViews() {
        views++;
    }
    
    int getEngagementScore() const {
        return (likes.size() * 10) + (comments.size() * 5) + views;
    }
};
```

### 2. Threaded Comment System 💬

```cpp
class Comment {
public:
    // Create top-level comment
    Comment(User* author, Post* post, string content) {
        this->commentId = generateUUID();
        this->author = author;
        this->post = post;
        this->content = content;
        this->parentComment = nullptr;
        this->createdAt = DateTime::now();
        this->isModerated = false;
    }
    
    // Create reply to another comment
    Comment* reply(User* user, const string& replyContent) {
        Comment* replyComment = new Comment(user, post, replyContent);
        replyComment->parentComment = this;
        replies.push_back(replyComment);
        NotificationSystem::notifyNewReply(this, replyComment);
        return replyComment;
    }
    
    // Display threaded structure
    void displayThread(int indentLevel = 0) const {
        string indent(indentLevel * 2, ' ');
        cout << indent << author->getUsername() << ": " << content << "\n";
        cout << indent << "↳ " << likes.size() << " likes | ";
        cout << replies.size() << " replies\n";
        
        for (Comment* reply : replies) {
            reply->displayThread(indentLevel + 1);
        }
    }
    
    // Moderation
    void moderate() {
        if (containsInappropriateContent()) {
            isModerated = true;
            content = "[This comment has been moderated]";
        }
    }
};
```

### 3. Role-Based Access Control 👥

```cpp
enum class UserRole {
    ADMIN,      // Full system access
    AUTHOR,     // Can create and manage own posts
    COMMENTER   // Can only comment on posts
};

class PermissionManager {
public:
    // Check post creation permission
    bool canCreatePost(User* user) {
        return user->getRole() == UserRole::ADMIN || 
               user->getRole() == UserRole::AUTHOR;
    }
    
    // Check post edit permission
    bool canEditPost(User* user, Post* post) {
        if (user->getRole() == UserRole::ADMIN) return true;
        if (post->getAuthor() == user) return true;
        return false;
    }
    
    // Check post deletion permission
    bool canDeletePost(User* user, Post* post) {
        if (user->getRole() == UserRole::ADMIN) return true;
        if (user->getRole() == UserRole::AUTHOR && 
            post->getAuthor() == user) return true;
        return false;
    }
    
    // Check moderation permission
    bool canModerateComments(User* user) {
        return user->getRole() == UserRole::ADMIN;
    }
    
    // Check user management permission
    bool canManageUsers(User* user) {
        return user->getRole() == UserRole::ADMIN;
    }
};
```

**Permission Matrix**:

| Action | Admin | Author | Commenter |
|--------|-------|--------|-----------|
| Create Post | ✅ | ✅ | ❌ |
| Edit Own Post | ✅ | ✅ | ❌ |
| Edit Any Post | ✅ | ❌ | ❌ |
| Delete Own Post | ✅ | ✅ | ❌ |
| Delete Any Post | ✅ | ❌ | ❌ |
| Comment on Post | ✅ | ✅ | ✅ |
| Moderate Comments | ✅ | ❌ | ❌ |
| Manage Users | ✅ | ❌ | ❌ |
| View Analytics | ✅ | Own Posts | ❌ |

### 4. Content Categorization 🏷️

```cpp
class Category {
private:
    string name;
    string description;
    vector<Post*> posts;
    
public:
    void addPost(Post* post) {
        posts.push_back(post);
        post->setCategory(this);
    }
    
    vector<Post*> getPosts() const {
        return posts;
    }
    
    int getPostCount() const {
        return posts.size();
    }
};

// Predefined categories
enum class CategoryType {
    TECHNOLOGY,
    LIFESTYLE,
    TRAVEL,
    FOOD,
    EDUCATION,
    ENTERTAINMENT,
    BUSINESS,
    HEALTH,
    SPORTS,
    UNCATEGORIZED
};

// Tag system for flexible organization
class Tag {
private:
    string name;
    vector<Post*> taggedPosts;
    
public:
    void tagPost(Post* post) {
        taggedPosts.push_back(post);
        post->addTag(this);
    }
    
    vector<Post*> getPostsWithTag() const {
        return taggedPosts;
    }
};
```

### 5. Full-Text Search Engine 🔍

```cpp
class SearchEngine {
private:
    map<string, vector<Post*>> invertedIndex;
    set<string> stopWords;
    
    // Build inverted index
    void indexPost(Post* post) {
        vector<string> words = tokenize(post->getContent());
        for (const string& word : words) {
            if (!isStopWord(word)) {
                invertedIndex[toLowerCase(word)].push_back(post);
            }
        }
    }
    
public:
    // Search posts
    vector<Post*> search(const string& query) {
        vector<string> queryWords = tokenize(query);
        map<Post*, int> scores;
        
        for (const string& word : queryWords) {
            string lowerWord = toLowerCase(word);
            if (invertedIndex.count(lowerWord)) {
                for (Post* post : invertedIndex[lowerWord]) {
                    scores[post]++;
                }
            }
        }
        
        // Sort by relevance
        return sortByScore(scores);
    }
    
    // Advanced search
    vector<Post*> advancedSearch(const SearchCriteria& criteria) {
        vector<Post*> results;
        
        // Search by title
        if (!criteria.title.empty()) {
            results = searchByTitle(criteria.title);
        }
        
        // Filter by author
        if (criteria.author != nullptr) {
            results = filterByAuthor(results, criteria.author);
        }
        
        // Filter by category
        if (criteria.category != CategoryType::UNCATEGORIZED) {
            results = filterByCategory(results, criteria.category);
        }
        
        // Filter by tags
        if (!criteria.tags.empty()) {
            results = filterByTags(results, criteria.tags);
        }
        
        // Filter by date range
        if (criteria.startDate.isValid()) {
            results = filterByDateRange(results, 
                                       criteria.startDate, 
                                       criteria.endDate);
        }
        
        return results;
    }
};
```

### 6. Notification System 🔔

```cpp
enum class NotificationType {
    NEW_COMMENT,        // Someone commented on your post
    NEW_REPLY,          // Someone replied to your comment
    NEW_FOLLOWER,       // Someone followed you
    POST_LIKED,         // Someone liked your post
    COMMENT_LIKED,      // Someone liked your comment
    MENTION,            // Someone mentioned you
    NEW_POST_FROM_FOLLOWING  // Someone you follow posted
};

class Notification {
private:
    string notificationId;
    User* recipient;
    NotificationType type;
    string message;
    DateTime createdAt;
    bool isRead;
    
public:
    Notification(User* user, NotificationType type, string msg) {
        this->notificationId = generateUUID();
        this->recipient = user;
        this->type = type;
        this->message = msg;
        this->createdAt = DateTime::now();
        this->isRead = false;
    }
    
    void markAsRead() {
        isRead = true;
    }
    
    string toString() const {
        string typeStr = getTypeString();
        string timeStr = createdAt.getRelativeTime(); // "2 hours ago"
        return "[" + typeStr + "] " + message + " (" + timeStr + ")";
    }
};

class NotificationSystem {
private:
    map<User*, vector<Notification*>> userNotifications;
    
public:
    void notifyNewComment(Post* post, Comment* comment) {
        User* author = post->getAuthor();
        string msg = comment->getAuthor()->getUsername() + 
                    " commented on your post: \"" + post->getTitle() + "\"";
        
        Notification* notif = new Notification(
            author, 
            NotificationType::NEW_COMMENT, 
            msg
        );
        
        userNotifications[author].push_back(notif);
    }
    
    void notifyNewFollower(User* user, User* follower) {
        string msg = follower->getUsername() + " started following you";
        Notification* notif = new Notification(
            user, 
            NotificationType::NEW_FOLLOWER, 
            msg
        );
        
        userNotifications[user].push_back(notif);
    }
    
    vector<Notification*> getUnreadNotifications(User* user) {
        vector<Notification*> unread;
        for (Notification* notif : userNotifications[user]) {
            if (!notif->isRead()) {
                unread.push_back(notif);
            }
        }
        return unread;
    }
};
```

### 7. Analytics & Statistics 📊

```cpp
class Analytics {
public:
    // User statistics
    struct UserStats {
        int totalPosts;
        int totalComments;
        int totalLikes;
        int totalViews;
        double averagePostLength;
        Post* mostPopularPost;
    };
    
    UserStats getUserStatistics(User* user) {
        UserStats stats;
        vector<Post*> posts = user->getPosts();
        
        stats.totalPosts = posts.size();
        stats.totalComments = 0;
        stats.totalLikes = 0;
        stats.totalViews = 0;
        
        for (Post* post : posts) {
            stats.totalComments += post->getCommentCount();
            stats.totalLikes += post->getLikeCount();
            stats.totalViews += post->getViews();
        }
        
        stats.averagePostLength = calculateAverageLength(posts);
        stats.mostPopularPost = findMostPopular(posts);
        
        return stats;
    }
    
    // Platform statistics
    struct PlatformStats {
        int totalUsers;
        int totalPosts;
        int totalComments;
        vector<Post*> trendingPosts;
        vector<User*> topAuthors;
        map<CategoryType, int> postsByCategory;
    };
    
    PlatformStats getPlatformStatistics() {
        // Aggregate platform-wide data
        // Return comprehensive statistics
    }
    
    // Trending algorithm
    vector<Post*> getTrendingPosts(int count = 10) {
        vector<Post*> allPosts = blogManager->getAllPosts();
        
        // Calculate trending score
        for (Post* post : allPosts) {
            int recencyScore = calculateRecencyScore(post);
            int engagementScore = post->getEngagementScore();
            post->trendingScore = recencyScore * 0.3 + engagementScore * 0.7;
        }
        
        // Sort by trending score
        sort(allPosts.begin(), allPosts.end(), 
             [](Post* a, Post* b) { 
                 return a->trendingScore > b->trendingScore; 
             });
        
        return vector<Post*>(allPosts.begin(), 
                            allPosts.begin() + min(count, (int)allPosts.size()));
    }
};
```

---

## 🎮 Usage Examples

### Example 1: Creating a Blog Post

```cpp
// Authenticate user (from v2)
AuthenticationManager& auth = AuthenticationManager::getInstance();
User* currentUser = auth.authenticateUser("john_author", "password123");

// Check permissions
PermissionManager permMgr;
if (!permMgr.canCreatePost(currentUser)) {
    cout << "You don't have permission to create posts.\n";
    return;
}

// Create post
BlogManager& blogMgr = BlogManager::getInstance();
Post* newPost = blogMgr.createPost(
    currentUser,
    "10 Tips for Better C++ Code",
    "Here are my top tips for writing clean C++ code..."
);

// Add metadata
newPost->setCategory(CategoryType::TECHNOLOGY);
newPost->addTag("C++");
newPost->addTag("Programming");
newPost->addTag("Best Practices");

// Publish
newPost->publish();

cout << "✓ Post published successfully!\n";
cout << "Post ID: " << newPost->getId() << "\n";
```

### Example 2: Commenting on a Post

```cpp
// Find post
Post* post = blogMgr.getPost("post-uuid-12345");

if (post == nullptr) {
    cout << "Post not found!\n";
    return;
}

// Create comment
Comment* comment = new Comment(
    currentUser,
    post,
    "Great article! Very helpful tips."
);

post->addComment(comment);

// Reply to another comment
Comment* existingComment = post->getComments()[0];
Comment* reply = existingComment->reply(
    currentUser,
    "I agree! Point #3 was especially useful."
);

cout << "✓ Comment added successfully!\n";
```

### Example 3: Searching for Content

```cpp
SearchEngine& searchEngine = SearchEngine::getInstance();

// Simple search
vector<Post*> results = searchEngine.search("C++ templates");

cout << "Found " << results.size() << " posts:\n";
for (Post* post : results) {
    cout << "- " << post->getTitle() 
         << " by " << post->getAuthor()->getUsername() << "\n";
}

// Advanced search
SearchCriteria criteria;
criteria.title = "programming";
criteria.category = CategoryType::TECHNOLOGY;
criteria.tags = {"C++", "Tutorial"};
criteria.startDate = DateTime::parse("2024-01-01");

vector<Post*> advancedResults = searchEngine.advancedSearch(criteria);
```

### Example 4: Viewing Notifications

```cpp
NotificationSystem& notifSystem = NotificationSystem::getInstance();

// Get unread notifications
vector<Notification*> unread = notifSystem.getUnreadNotifications(currentUser);

cout << "You have " << unread.size() << " new notifications:\n\n";

for (Notification* notif : unread) {
    cout << notif->toString() << "\n";
    notif->markAsRead();
}

// Check specific notification types
int newComments = notifSystem.getUnreadCountByType(
    currentUser, 
    NotificationType::NEW_COMMENT
);

cout << "\n" << newComments << " new comments on your posts\n";
```

### Example 5: Viewing Analytics

```cpp
Analytics analytics;

// User statistics
Analytics::UserStats stats = analytics.getUserStatistics(currentUser);

cout << "Your Statistics:\n";
cout << "─────────────────\n";
cout << "Total Posts: " << stats.totalPosts << "\n";
cout << "Total Comments: " << stats.totalComments << "\n";
cout << "Total Likes: " << stats.totalLikes << "\n";
cout << "Total Views: " << stats.totalViews << "\n";
cout << "Average Post Length: " << stats.averagePostLength << " words\n";

if (stats.mostPopularPost != nullptr) {
    cout << "Most Popular Post: " << stats.mostPopularPost->getTitle() << "\n";
    cout << "  └─ " << stats.mostPopularPost->getLikeCount() << " likes\n";
}

// Platform trending
vector<Post*> trending = analytics.getTrendingPosts(5);
cout << "\n📈 Trending Posts:\n";
for (int i = 0; i < trending.size(); i++) {
    cout << (i+1) << ". " << trending[i]->getTitle() << "\n";
    cout << "   by " << trending[i]->getAuthor()->getUsername() << "\n";
}
```

---

## 🎮 Console Interface Preview

### Main Menu (Logged In)

```
╔════════════════════════════════════════════════════════════╗
║              CHRONICLE BLOG SYSTEM v3.0                    ║
║           Logged in as: john_author (Author)               ║
╠════════════════════════════════════════════════════════════╣
║                                                            ║
║  📝 POST MANAGEMENT                                        ║
║     1. Create New Post                                     ║
║     2. View My Posts                                       ║
║     3. Edit Post                                           ║
║     4. Delete Post                                         ║
║                                                            ║
║  🔍 BROWSE & DISCOVER                                      ║
║     5. Browse All Posts                                    ║
║     6. Search Posts                                        ║
║     7. View by Category                                    ║
║     8. Trending Posts                                      ║
║                                                            ║
║  💬 ENGAGEMENT                                             ║
║     9. View Notifications (3 new)                          ║
║     10. My Comments                                        ║
║                                                            ║
║  📊 ANALYTICS                                              ║
║     11. View My Statistics                                 ║
║                                                            ║
║  👤 ACCOUNT                                                ║
║     12. Profile Settings                                   ║
║     13. Logout                                             ║
║                                                            ║
╚════════════════════════════════════════════════════════════╝

Enter your choice (1-13): _
```

### Post View

```
╔════════════════════════════════════════════════════════════╗
║                  10 Tips for Better C++ Code               ║
╠════════════════════════════════════════════════════════════╣
║ Author: john_author                  📅 Feb 4, 2026        ║
║ Category: Technology                 👁 1,234 views        ║
║ Tags: #C++ #Programming #BestPractices                     ║
╠════════════════════════════════════════════════════════════╣
║                                                            ║
║ Here are my top tips for writing clean C++ code...        ║
║                                                            ║
║ 1. Use meaningful variable names                          ║
║ 2. Follow const-correctness                               ║
║ 3. Prefer RAII over manual resource management            ║
║ [... content continues ...]                               ║
║                                                            ║
╠════════════════════════════════════════════════════════════╣
║ ❤️ 156 likes  💬 23 comments                              ║
╠════════════════════════════════════════════════════════════╣
║                                                            ║
║ [L] Like Post  [C] Add Comment  [S] Share  [B] Back       ║
║                                                            ║
╚════════════════════════════════════════════════════════════╝
```

### Comment Thread

```
╔════════════════════════════════════════════════════════════╗
║                      COMMENTS (23)                         ║
╠════════════════════════════════════════════════════════════╣
║                                                            ║
║ 👤 alice_dev • 2 hours ago                                ║
║ Great article! Point #3 about RAII is crucial.            ║
║ ❤️ 12  💬 2 replies                                       ║
║                                                            ║
║   ↳ 👤 bob_coder • 1 hour ago                            ║
║     Absolutely! Smart pointers changed my life.           ║
║     ❤️ 5                                                  ║
║                                                            ║
║   ↳ 👤 john_author • 30 minutes ago                      ║
║     Thanks! RAII is definitely a game-changer.            ║
║     ❤️ 3                                                  ║
║                                                            ║
║ ────────────────────────────────────────────────────────  ║
║                                                            ║
║ 👤 charlie_cpp • 5 hours ago                              ║
║ Would love to see more examples of tip #7!                ║
║ ❤️ 8  💬 1 reply                                          ║
║                                                            ║
║   ↳ 👤 john_author • 4 hours ago                         ║
║     Good idea! I'll create a follow-up post.              ║
║     ❤️ 4                                                  ║
║                                                            ║
╚════════════════════════════════════════════════════════════╝

[Type your comment] ________________________________
[Enter to post] [ESC to cancel]
```

---

## 🚀 Getting Started

### Prerequisites

```
- Visual Studio 2022
- C++17 or higher
- All v2 dependencies (OpenSSL, etc.)
```

### Installation

1. **Clone repository**:
   ```bash
   git clone https://github.com/apdalah/Cpp-Evolution-Lab.git
   cd Cpp-Evolution-Lab/v3-chronicle
   ```

2. **Build**:
   ```
   Open Cpp-Evolution-Lab.sln
   Set "v3-chronicle" as startup project
   Build → Build Solution (Ctrl+Shift+B)
   ```

3. **Run**:
   ```
   Debug → Start Debugging (F5)
   ```

---

## 📊 Metrics

```
Estimated Metrics:
─────────────────────────────────────────
Total Classes:        20+
Lines of Code:        ~2,500
Code Files:           30+
Storage Files:        6
Features:             50+
User Roles:           3
Design Patterns:      8+
```

---

## 🎓 Learning Outcomes

This version demonstrates:

### Advanced OOP Concepts
- ✅ Complex class hierarchies
- ✅ Association and aggregation
- ✅ Composition patterns
- ✅ Multiple inheritance scenarios

### Design Patterns
- ✅ Singleton (BlogManager)
- ✅ Factory (PostFactory)
- ✅ Observer (Notification system)
- ✅ Strategy (Search algorithms)
- ✅ Composite (Comment threading)
- ✅ Builder (SearchCriteria)

### Data Structures
- ✅ Trees (comment threads)
- ✅ Graphs (user relationships)
- ✅ Hash maps (search index)
- ✅ Priority queues (trending algorithm)

### Algorithms
- ✅ Full-text search
- ✅ Sorting and ranking
- ✅ Graph traversal (followers)
- ✅ Recommendation algorithms

---

## 🔄 Evolution Path

### From v2 to v3

| Aspect | v2 (Guardian) | v3 (Chronicle) |
|--------|--------------|----------------|
| **Primary Focus** | Authentication | Content Management |
| **User Model** | Basic User class | Extended with roles, posts, follows |
| **Data Entities** | User only | User, Post, Comment, Category, Tag |
| **Features** | Login/Register | Full blogging platform |
| **Complexity** | Medium | High |
| **Classes** | ~8 | ~20 |
| **Lines of Code** | ~800 | ~2,500 |

### Next Steps → v4: Aesthetic

- Replace console UI with modern GUI
- Add visual post editor
- Implement responsive design
- Create dashboard views

---

## 🐛 Known Issues

1. File-based storage still used (addressed in v5)
2. Console-based UI (addressed in v4)
3. No concurrent user support (addressed in v5)
4. Limited search performance (indexed in v5)
5. No image/media support (added in v4/v5)

---

<div align="center">

### 📝 From simple auth to full blogging platform!

**Next Challenge**: Modern UI in v4: Aesthetic

[← Back to v2](../v2-guardian) | [Main Project](../README.md) | [Next: v4 →](../v4-aesthetic)

</div>
